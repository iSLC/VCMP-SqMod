// ------------------------------------------------------------------------------------------------
#include "Library/Worker.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
SQMODE_DECL_TYPENAME(SqWorker, _SC("SqWorker"))

// ------------------------------------------------------------------------------------------------
Worker::Container Worker::sm_Workers{};

// ------------------------------------------------------------------------------------------------
Thread::Thread( Worker * worker)
    : mWorker(worker)
    , mObject(worker)
    , mThread(&Worker::Start, worker)
{
}
// ------------------------------------------------------------------------------------------------
Thread::Thread(Thread && o) noexcept
    : mWorker(o.mWorker)
    , mObject(std::forward< LightObj >(o.mObject))
    , mThread(std::forward< std::thread >(o.mThread))
{
    o.mWorker = nullptr;
}
// ------------------------------------------------------------------------------------------------
Worker::Worker(SQInteger stack, String && str, size_t h)
    : m_PendingJobs(4096), m_FinishedJobs(4096)
    , m_Running()
    , m_VM(nullptr)
    , m_Mutex()
    , m_Hash(h)
    , m_Name(std::forward< String >(str))
    , m_StackSize(stack)
{
}
// ------------------------------------------------------------------------------------------------
Worker::~Worker()
{
    // Instruct the thread to stop whenever possible
    Stop();
    // Locate our self in the list
    std::unique_ptr< Thread > & t = sm_Workers[m_Hash];
    // Wait for the thread to finish
    if (t->mThread.joinable())
    {
        t->mThread.join();
    }
    // Remove ourselves from the list
    sm_Workers.erase(m_Hash);
}

// ------------------------------------------------------------------------------------------------
void Worker::Terminate()
{
    // Attempt to stop workers
    for (auto & t : sm_Workers)
    {
        // Tell the thread to stop as soon as it can
        t.second->mWorker->Stop();
        // Wait for it to stop
        if (t.second->mThread.joinable())
        {
            t.second->mThread.join();
        }
    }
    // Simply get rid of them
    sm_Workers.clear();
}
// ------------------------------------------------------------------------------------------------
void Worker::Process(size_t jobs)
{
    std::vector< Worker * > workers;
    workers.reserve(sm_Workers.size());
    for (auto & t : sm_Workers)
    {
        workers.push_back(t.second->mWorker);
    }
    for (auto & t : workers)
    {
        for (size_t n = 0; n < jobs; ++n)
        {
            std::unique_ptr< Job > job;
            // Try to get a job from the queue
            if (!t->m_FinishedJobs.try_dequeue(job))
            {
                break; // No jobs
            }
            // Does it have a callback?
            if (!job->mCallback.IsNull())
            {
                job->mCallback.Execute();
            }
        }
    }
}
// ------------------------------------------------------------------------------------------------
LightObj Worker::Create(SQInteger stack, StackStrF & str)
{
    HSQUIRRELVM vm = SqVM();
	// Make sure there's a name
	if (str.mLen <= 0)
	{
		STHROWF("Invalid or empty worker name");
	}
	// Extract the worker name
    String name(str.mPtr, static_cast< size_t >(str.mLen));
    // Create the name hash
    size_t name_hash = std::hash< String >{}(name);
    // Make sure this worker doesn't exist
    if (sm_Workers.exists(name_hash))
    {
        STHROWF("Worker already exists");
    }
    // Attempt to create a routine instance
    DeleteGuard< Worker > dg(new Worker(stack, std::move(name), name_hash));
    ClassType< Worker >::PushInstance(vm, dg.Get());
    Worker * worker = dg.Grab();
    // Create the worker thread
    std::unique_ptr< Thread > & th = sm_Workers.emplace_back(name_hash, new Thread{worker});
    // Return the worker object
    return th->mObject;
}
// ------------------------------------------------------------------------------------------------
void Worker::Start()
{
    // Initialize
    {
        // Acquire exclusive access to this instance
        std::lock_guard< std::mutex > lg(m_Mutex);
        // This should never be the case but why not
        if (m_VM)
        {
            STHROWF("Worker was already started.");
        }
        // Create the JS state
        m_VM = sq_open(m_StackSize);
        // Tell the VM to use these functions to output user on error messages
        sq_setprintfunc(m_VM, PrintFunc, ErrorFunc);
        // This is now running
        m_Running.test_and_set();
    }
    // Process
    while (m_Running.test_and_set())
    {
        // Acquire exclusive access to this instance
        std::lock_guard< std::mutex > lg(m_Mutex);
        // Do the actual processing
        Work();
    }
    // Cleanup
    {
        // Acquire exclusive access to this instance
        std::lock_guard< std::mutex > lg(m_Mutex);
        // We're out of the process loop
        sq_close(m_VM);
    }
}
// ------------------------------------------------------------------------------------------------
void Worker::Work()
{
    std::unique_ptr< Job > job;
    // Try to get a job from the queue
    if (!m_PendingJobs.try_dequeue(job))
    {
        using namespace std::chrono_literals;
        // Do not hammer the CPU if there are no jobs
        std::this_thread::sleep_for(50ms);
        // Try again
        return;
    }
    // Identify the job type
    switch (job->mType)
    {
        // This type of job demands no work
        case Job::Type::Null: break;
        case Job::Type::Stop:

        break;
        case Job::Type::Eval: {
            sq_compilebuffer(m_VM, job->mPayload.data(), job->mPayload.size(), _SC("eval"), SQTrue);
            SQInteger top = sq_gettop(m_VM);
            sq_pushroottable(m_VM);
            sq_call(m_VM, 1, false, true);
            sq_settop(m_VM, top);
        } break;
        case Job::Type::Exec:

        break;
        // We're not qualified for this job
        default: break;
    }
    // This job was finished
    m_FinishedJobs.enqueue(std::move(job));
}
// ------------------------------------------------------------------------------------------------
void Worker::PrintFunc(HSQUIRRELVM /*vm*/, CSStr msg, ...)
{
    // Initialize the variable argument list
    va_list args;
    va_start(args, msg);
    // Forward the message to the logger
    std::vprintf(msg, args);
    std::puts("");
    // Finalize the variable argument list
    va_end(args);
}

// ------------------------------------------------------------------------------------------------
void Worker::ErrorFunc(HSQUIRRELVM /*vm*/, CSStr msg, ...)
{
    // Initialize the variable argument list
    va_list args;
    va_start(args, msg);
    // Tell the logger to display debugging information
    std::vprintf(msg, args);
    std::puts("");
    // Finalize the variable argument list
    va_end(args);
}
// ------------------------------------------------------------------------------------------------
void TerminateWorkers()
{
    Worker::Terminate();
}
// ================================================================================================
void Register_Worker(HSQUIRRELVM vm)
{
    Table thns(vm);

    thns.Bind(_SC("Worker"),
        Class< Worker, NoConstructor< Worker > >(vm, SqWorker::Str)
        // Meta-methods
        .SquirrelFunc(_SC("_typename"), &SqWorker::Fn)
        // Properties
        .Prop(_SC("Name"), &Worker::GetName)
        // Core Methods
        .CbFunc(_SC("Evaluate"), &Worker::Evaluate)
        // Static Member Methods
    );

    thns.FmtFunc(_SC("Process"), &Worker::Process);
    thns.FmtFunc(_SC("Create"), &Worker::Create);

    RootTable(vm).Bind(_SC("SqThread"), thns);
}

} // Namespace:: SqMod
