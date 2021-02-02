// ------------------------------------------------------------------------------------------------
#include "PocoLib/Net.hpp"

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------


// ================================================================================================
void Register_POCO_Net(HSQUIRRELVM vm, Table &)
{
    Table ns(vm);

    RootTable(vm).Bind(_SC("SqNet"), ns);
}

} // Namespace:: SqMod
