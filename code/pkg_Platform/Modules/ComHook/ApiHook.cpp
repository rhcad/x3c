#ifdef _WIN32
#include <UtilFunc/PluginInc.h>
#include <UtilFunc/LoadDllHelper.h>

static PIMAGE_THUNK_DATA FindThunkData(LPCSTR dllname);
static PROC* FindFunctionAddress(PIMAGE_THUNK_DATA thunk, PROC oldproc);
static bool ReplaceFunction(PROC* addr, PROC newproc);

bool HookModuleFunction(LPCSTR dllname, PROC oldproc, PROC newproc)
{
    ASSERT(dllname && oldproc && newproc);

    PIMAGE_THUNK_DATA thunk = FindThunkData(dllname);
    PROC* pfunc = thunk ? FindFunctionAddress(thunk, oldproc) : NULL;

    return pfunc && ReplaceFunction(pfunc, newproc);
}

PIMAGE_THUNK_DATA FindThunkData(LPCSTR dllname)
{
    HMODULE hmod = GetModuleHandleW(NULL);
    PIMAGE_IMPORT_DESCRIPTOR importDesc = NULL;

    // Get the import directory of the current process.
    //
    try
    {
        typedef PVOID (__stdcall * FUNC)(PVOID, BOOLEAN, USHORT, PULONG);
        LoadDllHelper dll(L"Dbghelp.dll");
        FUNC func = (FUNC)dll.GetFunc("ImageDirectoryEntryToData");
        ULONG size = 0;
        importDesc = !func ? NULL : (PIMAGE_IMPORT_DESCRIPTOR)func(
            hmod, true, IMAGE_DIRECTORY_ENTRY_IMPORT, &size);
    }
    catch (...)
    {
    }

    if (importDesc == NULL)
    {
        return NULL;
    }

    // Find the import address table of the module.
    //
    for (; importDesc->Name; importDesc++)
    {
        LPCSTR name = (LPCSTR)((PBYTE)hmod + importDesc->Name);

        if (_stricmp(name, dllname) == 0)
        {
            return (PIMAGE_THUNK_DATA)((PBYTE)hmod + importDesc->FirstThunk);
        }
    }

    return NULL;
}

PROC* FindFunctionAddress(PIMAGE_THUNK_DATA thunk, PROC oldproc)
{
    for (; thunk->u1.Function; thunk++)
    {
        PROC* poldfunc = (PROC*) &(thunk->u1.Function);

        if (*poldfunc == oldproc)
        {
            return poldfunc;
        }
    }

    return NULL;
}

bool ReplaceFunction(PROC* addr, PROC newproc)
{
    bool ret = !!WriteProcessMemory(GetCurrentProcess(),
        addr, &newproc, sizeof(newproc), NULL);

    if (!ret && ERROR_NOACCESS == GetLastError())
    {
        DWORD oldProtect = 0;

        if (VirtualProtect(addr, sizeof(*addr),
            PAGE_WRITECOPY, &oldProtect))
        {
            ret = !!WriteProcessMemory(GetCurrentProcess(),
                addr, &newproc, sizeof(newproc), NULL);
            VirtualProtect(addr, sizeof(*addr), oldProtect, &oldProtect);
        }
    }

    return ret;
}

#endif // _WIN32
