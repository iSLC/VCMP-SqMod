// ------------------------------------------------------------------------------------------------
#include "Entity/Checkpoint.hpp"
#include "Entity/Player.hpp"
#include "Base/Color4.hpp"
#include "Base/Vector3.hpp"
#include "Core.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
Color4      CCheckpoint::s_Color4;
Vector3     CCheckpoint::s_Vector3;

// ------------------------------------------------------------------------------------------------
Uint32      CCheckpoint::s_ColorR;
Uint32      CCheckpoint::s_ColorG;
Uint32      CCheckpoint::s_ColorB;
Uint32      CCheckpoint::s_ColorA;

// ------------------------------------------------------------------------------------------------
const Int32 CCheckpoint::Max = SQMOD_CHECKPOINT_POOL;

// ------------------------------------------------------------------------------------------------
SQInteger CCheckpoint::Typename(HSQUIRRELVM vm)
{
    static SQChar name[] = _SC("SqCheckpoint");
    sq_pushstring(vm, name, sizeof(name));
    return 1;
}

// ------------------------------------------------------------------------------------------------
CCheckpoint::CCheckpoint(Int32 id)
    : m_ID(VALID_ENTITYGETEX(id, SQMOD_CHECKPOINT_POOL))
    , m_Tag(ToStrF("%d", id))
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
CCheckpoint::~CCheckpoint()
{
    /* ... */
}

// ------------------------------------------------------------------------------------------------
Int32 CCheckpoint::Cmp(const CCheckpoint & o) const
{
    if (m_ID == o.m_ID)
        return 0;
    else if (m_ID > o.m_ID)
        return 1;
    else
        return -1;
}

// ------------------------------------------------------------------------------------------------
const String & CCheckpoint::ToString() const
{
    return m_Tag;
}

// ------------------------------------------------------------------------------------------------
const String & CCheckpoint::GetTag() const
{
    return m_Tag;
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetTag(CSStr tag)
{
    m_Tag.assign(tag);
}

// ------------------------------------------------------------------------------------------------
Object & CCheckpoint::GetData()
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return m_Data;
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetData(Object & data)
{
    // Validate the managed identifier
    Validate();
    // Apply the specified value
    m_Data = data;
}

// ------------------------------------------------------------------------------------------------
bool CCheckpoint::Destroy(Int32 header, Object & payload)
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    return _Core->DelCheckpoint(m_ID, header, payload);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::BindEvent(Int32 evid, Object & env, Function & func) const
{
    // Validate the managed identifier
    Validate();
    // Obtain the function instance called for this event
    Function & event = _Core->GetCheckpointEvent(m_ID, evid);
    // Is the specified callback function null?
    if (func.IsNull())
        event.Release(); // Then release the current callback
    // Assign the specified environment and function
    else
        event = Function(env.GetVM(), env, func.GetFunc());
}

// ------------------------------------------------------------------------------------------------
bool CCheckpoint::IsStreamedFor(CPlayer & player) const
{
    // Is the specified player even valid?
    if (!player.IsActive())
        SqThrowF("Invalid player argument: null");
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->IsCheckpointStreamedForPlayer(m_ID, player.GetID());
}

// ------------------------------------------------------------------------------------------------
Int32 CCheckpoint::GetWorld() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetCheckpointWorld(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetWorld(Int32 world) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetCheckpointWorld(m_ID, world);
}

// ------------------------------------------------------------------------------------------------
const Color4 & CCheckpoint::GetColor() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous color information, if any
    s_Color4.Clear();
    // Query the server for the color values
    _Func->GetCheckpointColor(m_ID, &s_ColorR, &s_ColorG, &s_ColorB, &s_ColorA);
    // Convert and assign the retrieved values
    s_Color4.Set(s_ColorR, s_ColorG, s_ColorB, s_ColorA);
    // Return the requested information
    return s_Color4;
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetColor(const Color4 & col) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetCheckpointColor(m_ID, col.r, col.g, col.b, col.a);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetColorEx(Uint8 r, Uint8 g, Uint8 b, Uint8 a) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetCheckpointColor(m_ID, r, g, b, a);
}

// ------------------------------------------------------------------------------------------------
const Vector3 & CCheckpoint::GetPosition() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous position information, if any
    s_Vector3.Clear();
    // Query the server for the position values
    _Func->GetCheckpointPos(m_ID, &s_Vector3.x, &s_Vector3.y, &s_Vector3.z);
    // Return the requested information
    return s_Vector3;
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetPosition(const Vector3 & pos) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetCheckpointPos(m_ID, pos.x, pos.y, pos.z);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetPositionEx(Float32 x, Float32 y, Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetCheckpointPos(m_ID, x, y, z);
}

// ------------------------------------------------------------------------------------------------
Float32 CCheckpoint::GetRadius() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetCheckpointRadius(m_ID);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetRadius(Float32 radius) const
{
    // Validate the managed identifier
    Validate();
    // Perform the requested operation
    _Func->SetCheckpointRadius(m_ID, radius);
}

// ------------------------------------------------------------------------------------------------
Object & CCheckpoint::GetOwner() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Core->GetPlayer(_Func->GetCheckpointOwner(m_ID)).mObj;
}

// ------------------------------------------------------------------------------------------------
Int32 CCheckpoint::GetOwnerID() const
{
    // Validate the managed identifier
    Validate();
    // Return the requested information
    return _Func->GetCheckpointOwner(m_ID);
}

// ------------------------------------------------------------------------------------------------
Float32 CCheckpoint::GetPosX() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous position information, if any
    s_Vector3.x = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointPos(m_ID, &s_Vector3.x, NULL, NULL);
    // Return the requested information
    return s_Vector3.x;
}

// ------------------------------------------------------------------------------------------------
Float32 CCheckpoint::GetPosY() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous position information, if any
    s_Vector3.y = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointPos(m_ID, NULL, &s_Vector3.y, NULL);
    // Return the requested information
    return s_Vector3.y;
}

// ------------------------------------------------------------------------------------------------
Float32 CCheckpoint::GetPosZ() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous position information, if any
    s_Vector3.z = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointPos(m_ID, NULL, NULL, &s_Vector3.z);
    // Return the requested information
    return s_Vector3.z;
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetPosX(Float32 x) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointPos(m_ID, NULL, &s_Vector3.y, &s_Vector3.z);
    // Perform the requested operation
    _Func->SetCheckpointPos(m_ID, x, s_Vector3.y, s_Vector3.z);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetPosY(Float32 y) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointPos(m_ID, &s_Vector3.x, NULL, &s_Vector3.z);
    // Perform the requested operation
    _Func->SetCheckpointPos(m_ID, s_Vector3.x, y, s_Vector3.z);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetPosZ(Float32 z) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointPos(m_ID, &s_Vector3.x, &s_Vector3.y, NULL);
    // Perform the requested operation
    _Func->SetCheckpointPos(m_ID, s_Vector3.z, s_Vector3.y, z);
}

// ------------------------------------------------------------------------------------------------
Uint32 CCheckpoint::GetColR() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous color information, if any
    s_ColorR = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointColor(m_ID, &s_ColorR, NULL, NULL, NULL);
    // Return the requested information
    return s_ColorR;
}

// ------------------------------------------------------------------------------------------------
Uint32 CCheckpoint::GetColG() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous color information, if any
    s_ColorG = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointColor(m_ID, NULL, &s_ColorG, NULL, NULL);
    // Return the requested information
    return s_ColorG;
}

// ------------------------------------------------------------------------------------------------
Uint32 CCheckpoint::GetColB() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous color information, if any
    s_ColorB = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointColor(m_ID, NULL, NULL, &s_ColorB, NULL);
    // Return the requested information
    return s_ColorB;
}

// ------------------------------------------------------------------------------------------------
Uint32 CCheckpoint::GetColA() const
{
    // Validate the managed identifier
    Validate();
    // Clear previous color information, if any
    s_ColorA = 0;
    // Query the server for the requested component value
    _Func->GetCheckpointColor(m_ID, NULL, NULL, NULL, &s_ColorA);
    // Return the requested information
    return s_ColorA;
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetColR(Uint32 r) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointColor(m_ID, NULL, &s_ColorG, &s_ColorB, &s_ColorA);
    // Perform the requested operation
    _Func->SetCheckpointColor(m_ID, r, s_ColorG, s_ColorB, s_ColorA);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetColG(Uint32 g) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointColor(m_ID, &s_ColorR, NULL, &s_ColorB, &s_ColorA);
    // Perform the requested operation
    _Func->SetCheckpointColor(m_ID, s_ColorR, g, s_ColorB, s_ColorA);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetColB(Uint32 b) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointColor(m_ID, &s_ColorB, &s_ColorG, NULL, &s_ColorA);
    // Perform the requested operation
    _Func->SetCheckpointColor(m_ID, s_ColorB, s_ColorG, b, s_ColorA);
}

// ------------------------------------------------------------------------------------------------
void CCheckpoint::SetColA(Uint32 a) const
{
    // Validate the managed identifier
    Validate();
    // Retrieve the current values for unchanged components
    _Func->GetCheckpointColor(m_ID, &s_ColorA, &s_ColorG, &s_ColorB, NULL);
    // Perform the requested operation
    _Func->SetCheckpointColor(m_ID, s_ColorA, s_ColorG, s_ColorB, a);
}

// ------------------------------------------------------------------------------------------------
static Object & Checkpoint_CreateEx(CPlayer & player, Int32 world, Float32 x, Float32 y, Float32 z,
                            Uint8 r, Uint8 g, Uint8 b, Uint8 a, Float32 radius)
{
    return _Core->NewCheckpoint(player.GetID(), world, x, y, z, r, g, b, a, radius,
                                SQMOD_CREATE_DEFAULT, NullObject());
}

static Object & Checkpoint_CreateEx(CPlayer & player, Int32 world, Float32 x, Float32 y, Float32 z,
                            Uint8 r, Uint8 g, Uint8 b, Uint8 a, Float32 radius,
                            Int32 header, Object & payload)
{
    return _Core->NewCheckpoint(player.GetID(), world, x, y, z, r, g, b, a, radius, header, payload);
}

// ------------------------------------------------------------------------------------------------
static Object & Checkpoint_Create(CPlayer & player, Int32 world, const Vector3 & pos,
                            const Color4 & color, Float32 radius)
{
    return _Core->NewCheckpoint(player.GetID(), world, pos.x, pos.y, pos.z,
                                color.r, color.g, color.b, color.a, radius,
                                SQMOD_CREATE_DEFAULT, NullObject());
}

static Object & Checkpoint_Create(CPlayer & player, Int32 world, const Vector3 & pos,
                            const Color4 & color, Float32 radius, Int32 header, Object & payload)
{
    return _Core->NewCheckpoint(player.GetID(), world, pos.x, pos.y, pos.z,
                                color.r, color.g, color.b, color.a, radius, header, payload);
}

// ------------------------------------------------------------------------------------------------
static const Object & Checkpoint_FindByID(Int32 id)
{
    // Perform a range check on the specified identifier
    if (INVALID_ENTITYEX(id, SQMOD_CHECKPOINT_POOL))
        SqThrowF("The specified checkpoint identifier is invalid: %d", id);
    // Obtain the ends of the entity pool
    Core::Checkpoints::const_iterator itr = _Core->GetCheckpoints().cbegin();
    Core::Checkpoints::const_iterator end = _Core->GetCheckpoints().cend();
    // Process each entity in the pool
    for (; itr != end; ++itr)
    {
        // Does the identifier match the specified one?
        if (itr->mID == id)
            return itr->mObj; // Stop searching and return this entity
    }
    // Unable to locate a checkpoint matching the specified identifier
    return NullObject();
}

static const Object & Checkpoint_FindByTag(CSStr tag)
{
    // Perform a validity check on the specified tag
    if (!tag || *tag == 0)
        SqThrowF("The specified checkpoint tag is invalid: null/empty");
    // Obtain the ends of the entity pool
    Core::Checkpoints::const_iterator itr = _Core->GetCheckpoints().cbegin();
    Core::Checkpoints::const_iterator end = _Core->GetCheckpoints().cend();
    // Process each entity in the pool
    for (; itr != end; ++itr)
    {
        // Does this entity even exist and does the tag match the specified one?
        if (itr->mInst != nullptr && itr->mInst->GetTag().compare(tag) == 0)
            return itr->mObj; // Stop searching and return this entity
    }
    // Unable to locate a checkpoint matching the specified tag
    return NullObject();
}

// ================================================================================================
void Register_CCheckpoint(HSQUIRRELVM vm)
{
    RootTable(vm).Bind(_SC("SqCheckpoint"),
        Class< CCheckpoint, NoConstructor< CCheckpoint > >(vm, _SC("SqCheckpoint"))
        // Metamethods
        .Func(_SC("_cmp"), &CCheckpoint::Cmp)
        .SquirrelFunc(_SC("_typename"), &CCheckpoint::Typename)
        .Func(_SC("_tostring"), &CCheckpoint::ToString)
        // Static Values
        .SetStaticValue(_SC("MaxID"), CCheckpoint::Max)
        // Core Properties
        .Prop(_SC("ID"), &CCheckpoint::GetID)
        .Prop(_SC("Tag"), &CCheckpoint::GetTag, &CCheckpoint::SetTag)
        .Prop(_SC("Data"), &CCheckpoint::GetData, &CCheckpoint::SetData)
        .Prop(_SC("Active"), &CCheckpoint::IsActive)
        // Core Methods
        .Func(_SC("Bind"), &CCheckpoint::BindEvent)
        // Core Overloads
        .Overload< bool (CCheckpoint::*)(void) >(_SC("Destroy"), &CCheckpoint::Destroy)
        .Overload< bool (CCheckpoint::*)(Int32) >(_SC("Destroy"), &CCheckpoint::Destroy)
        .Overload< bool (CCheckpoint::*)(Int32, Object &) >(_SC("Destroy"), &CCheckpoint::Destroy)
        // Properties
        .Prop(_SC("World"), &CCheckpoint::GetWorld, &CCheckpoint::SetWorld)
        .Prop(_SC("Color"), &CCheckpoint::GetColor, &CCheckpoint::SetColor)
        .Prop(_SC("Pos"), &CCheckpoint::GetPosition, &CCheckpoint::SetPosition)
        .Prop(_SC("Position"), &CCheckpoint::GetPosition, &CCheckpoint::SetPosition)
        .Prop(_SC("Radius"), &CCheckpoint::GetRadius, &CCheckpoint::SetRadius)
        .Prop(_SC("Owner"), &CCheckpoint::GetOwner)
        .Prop(_SC("OwnerID"), &CCheckpoint::GetOwnerID)
        .Prop(_SC("X"), &CCheckpoint::GetPosX, &CCheckpoint::SetPosX)
        .Prop(_SC("Y"), &CCheckpoint::GetPosY, &CCheckpoint::SetPosY)
        .Prop(_SC("Z"), &CCheckpoint::GetPosZ, &CCheckpoint::SetPosZ)
        .Prop(_SC("R"), &CCheckpoint::GetColR, &CCheckpoint::SetColR)
        .Prop(_SC("G"), &CCheckpoint::GetColG, &CCheckpoint::SetColG)
        .Prop(_SC("B"), &CCheckpoint::GetColB, &CCheckpoint::SetColB)
        .Prop(_SC("A"), &CCheckpoint::GetColA, &CCheckpoint::SetColA)
        // Member Methods
        .Func(_SC("StreamedFor"), &CCheckpoint::IsStreamedFor)
        .Func(_SC("SetColor"), &CCheckpoint::SetColorEx)
        .Func(_SC("SetPos"), &CCheckpoint::SetPositionEx)
        .Func(_SC("SetPosition"), &CCheckpoint::SetPositionEx)
        // Static Functions
        .StaticFunc(_SC("FindByID"), &Checkpoint_FindByID)
        .StaticFunc(_SC("FindByTag"), &Checkpoint_FindByTag)
        // Static Overloads
        .StaticOverload< Object & (*)(CPlayer &, Int32, Float32, Float32, Float32, Uint8, Uint8, Uint8, Uint8, Float32) >
            (_SC("CreateEx"), &Checkpoint_CreateEx)
        .StaticOverload< Object & (*)(CPlayer &, Int32, Float32, Float32, Float32, Uint8, Uint8, Uint8, Uint8, Float32, Int32, Object &) >
            (_SC("CreateEx"), &Checkpoint_CreateEx)
        .StaticOverload< Object & (*)(CPlayer &, Int32, const Vector3 &, const Color4 &, Float32) >
            (_SC("Create"), &Checkpoint_Create)
        .StaticOverload< Object & (*)(CPlayer &, Int32, const Vector3 &, const Color4 &, Float32, Int32, Object &) >
            (_SC("Create"), &Checkpoint_Create)
    );
}

} // Namespace:: SqMod
