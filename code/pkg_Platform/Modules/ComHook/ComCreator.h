#ifndef _COMHOOK_COMCREATOR_H
#define _COMHOOK_COMCREATOR_H

class CComCreator
{
public:
    static bool Init();
    static void Free();

private:
    static HRESULT WINAPI Hook_CoCreateInstance(REFCLSID rclsid, 
        LPUNKNOWN pUnkOuter, DWORD dwClsContext, 
        REFIID riid, LPVOID FAR* ppv);
    static HRESULT CreateInstance(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);
};

#endif // _COMHOOK_COMCREATOR_H
