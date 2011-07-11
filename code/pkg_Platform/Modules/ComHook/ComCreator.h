#ifndef _COMHOOK_COMCREATOR_H
#define _COMHOOK_COMCREATOR_H

class CComCreator
{
public:
    static const PROC c_oldfunc;
    static HRESULT WINAPI Hook_CoCreateInstance(REFCLSID rclsid, 
        LPUNKNOWN pUnkOuter, DWORD dwClsContext, 
        REFIID riid, LPVOID FAR* ppv);

private:
    static HRESULT CreateInstance(REFCLSID rclsid, REFIID riid, LPVOID FAR* ppv);
    static HMODULE FindModule(const std::wstring& clsid);
};

#endif // _COMHOOK_COMCREATOR_H
