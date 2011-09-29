#ifndef _COMHOOK_COMCREATOR_H
#define _COMHOOK_COMCREATOR_H

class CComCreator
{
public:
    //! Replace API functions of the current process to hook CoCreateInstance.
    static bool Init();

    //! Restore API functions of the current process and unload COM modules.
    static void Free();

private:
    static HRESULT WINAPI Hook_CoCreateInstance(REFCLSID rclsid, 
        LPUNKNOWN pUnkOuter, DWORD dwClsContext, 
        REFIID riid, LPVOID* ppv);
    static HRESULT LocalCreateInstance(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
};

#endif // _COMHOOK_COMCREATOR_H
