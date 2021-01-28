#ifndef _REGISTER_HPP_
#define _REGISTER_HPP_

// ------------------------------------------------------------------------------------------------
#include <squirrelex.h>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
extern void Register_AABB(HSQUIRRELVM vm);
extern void Register_Circle(HSQUIRRELVM vm);
extern void Register_Color3(HSQUIRRELVM vm);
extern void Register_Color4(HSQUIRRELVM vm);
extern void Register_Quaternion(HSQUIRRELVM vm);
extern void Register_Sphere(HSQUIRRELVM vm);
extern void Register_Vector2(HSQUIRRELVM vm);
extern void Register_Vector2i(HSQUIRRELVM vm);
extern void Register_Vector3(HSQUIRRELVM vm);
extern void Register_Vector4(HSQUIRRELVM vm);
extern void Register_Base(HSQUIRRELVM vm);
extern void Register_Algo(HSQUIRRELVM vm);

// ------------------------------------------------------------------------------------------------
extern void Register_CBlip(HSQUIRRELVM vm);
extern void Register_CCheckpoint(HSQUIRRELVM vm);
extern void Register_CKeybind(HSQUIRRELVM vm);
extern void Register_CObject(HSQUIRRELVM vm);
extern void Register_CPickup(HSQUIRRELVM vm);
extern void Register_CPlayer(HSQUIRRELVM vm);
extern void Register_CVehicle(HSQUIRRELVM vm);

// ------------------------------------------------------------------------------------------------
extern void Register_Chrono(HSQUIRRELVM vm);
extern void Register_Crypt(HSQUIRRELVM vm);
#ifdef SQ_ENABLE_CURL
extern void Register_CURL(HSQUIRRELVM vm);
#endif
extern void Register_IO(HSQUIRRELVM vm);
extern void Register_Job(HSQUIRRELVM vm);
extern void Register_MMDB(HSQUIRRELVM vm);
#ifdef SQ_ENABLE_MYSQL
extern void Register_MySQL(HSQUIRRELVM vm);
#endif
extern void Register_Numeric(HSQUIRRELVM vm);
extern void Register_Socket(HSQUIRRELVM vm);
extern void Register_SQLite(HSQUIRRELVM vm);
extern void Register_String(HSQUIRRELVM vm);
extern void Register_System(HSQUIRRELVM vm);
extern void Register_Utils(HSQUIRRELVM vm);
extern void Register_Worker(HSQUIRRELVM vm);
extern void Register_Web(HSQUIRRELVM vm);
extern void Register_XML(HSQUIRRELVM vm);

// ------------------------------------------------------------------------------------------------
extern void Register_Constants(HSQUIRRELVM vm);
extern void Register_Log(HSQUIRRELVM vm);
extern void Register_Core(HSQUIRRELVM vm);
extern void Register_Command(HSQUIRRELVM vm);
extern void Register_Privilege(HSQUIRRELVM vm);
extern void Register_Routine(HSQUIRRELVM vm);
extern void RegisterTask(HSQUIRRELVM vm);

// ------------------------------------------------------------------------------------------------
extern void Register_Misc(HSQUIRRELVM vm);
extern void Register_Areas(HSQUIRRELVM vm);
extern void Register_Signal(HSQUIRRELVM vm);

// ------------------------------------------------------------------------------------------------
bool RegisterAPI(HSQUIRRELVM vm)
{
    Register_AABB(vm);
    Register_Circle(vm);
    Register_Color3(vm);
    Register_Color4(vm);
    Register_Quaternion(vm);
    Register_Sphere(vm);
    Register_Vector2(vm);
    Register_Vector2i(vm);
    Register_Vector3(vm);
    Register_Vector4(vm);
    Register_Base(vm);
    Register_Algo(vm);

    Register_CBlip(vm);
    Register_CCheckpoint(vm);
    Register_CKeybind(vm);
    Register_CObject(vm);
    Register_CPickup(vm);
    Register_CPlayer(vm);
    Register_CVehicle(vm);

    Register_Chrono(vm);
    Register_Crypt(vm);
#ifdef SQ_ENABLE_CURL
    Register_CURL(vm);
#endif
    Register_IO(vm);
    Register_Job(vm);
    Register_MMDB(vm);
#ifdef SQ_ENABLE_MYSQL
    Register_MySQL(vm);
#endif
    Register_Numeric(vm);
    Register_Socket(vm);
    Register_SQLite(vm);
    Register_String(vm);
    Register_System(vm);
    Register_Utils(vm);
    Register_Worker(vm);
    Register_Web(vm);
    Register_XML(vm);

    Register_Constants(vm);
    Register_Log(vm);
    Register_Core(vm);
    Register_Command(vm);
    Register_Privilege(vm);
    Register_Routine(vm);
    RegisterTask(vm);

    Register_Misc(vm);
    Register_Areas(vm);
    Register_Signal(vm);

    return true;
}

} // Namespace:: SqMod

#endif // _REGISTER_HPP_
