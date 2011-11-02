#ifndef _COMHOOK_COMCREATOR_H
#define _COMHOOK_COMCREATOR_H

class CComCreator
{
public:
    static void Free();
    static bool Hook(HMODULE hmod);
    static bool Unhook(HMODULE hmod);

private:
    static HRESULT WINAPI Hook_CoCreateInstance(REFCLSID rclsid, 
        LPUNKNOWN pUnkOuter, DWORD dwClsContext, 
        REFIID riid, LPVOID* ppv);
    static HRESULT LocalCreateInstance(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
};

#endif // _COMHOOK_COMCREATOR_H
