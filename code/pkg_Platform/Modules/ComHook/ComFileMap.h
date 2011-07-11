#ifndef _COMHOOK_COMFILEMAP_H
#define _COMHOOK_COMFILEMAP_H

class CComFileMap
{
public:
    CComFileMap();
    ~CComFileMap();

    void Free();
    std::wstring GetComFile(const std::wstring& clsid);

private:
    void LoadMapFile(const std::wstring& filename);

    bool    m_loaded;
    std::map<std::wstring, std::wstring>    m_map;
};

class CComModules
{
public:
    CComModules();
    ~CComModules();

    void Free();
    HMODULE GetModule(const std::wstring& filename);
};

#endif // _COMHOOK_COMFILEMAP_H

