#include <UtilFunc/PluginInc.h>
#include "ComFileMap.h"
#include <UtilFunc/ScanFiles.h>
#include <UtilFunc/RelToAbs.h>
#include <Xml/Ix_ConfigXml.h>
#include <Xml/Cx_ConfigSection.h>
#include <PluginManager/Ix_PluginDelayLoad.h>
#include <UtilFunc/SysErrStr.h>

// CComFileMap
//

CComFileMap::CComFileMap() : m_loaded(false)
{
}

CComFileMap::~CComFileMap()
{
    Free();
}

void CComFileMap::Free()
{
    m_map.clear();
}

std::wstring CComFileMap::GetComFile(const std::wstring& clsid)
{
    if (!m_loaded)
    {
        std::vector<std::wstring> files;
        x3::CScanFilesByExtension scanner(&files, L".xml");
        std::wstring path(x3::RelToAbsWithPlugin(L"../config/commap", false));

        x3::ScanFiles(&scanner, path.c_str(), true);
        m_loaded = true;

        for (std::vector<std::wstring>::iterator it = files.begin();
            it != files.end(); ++it)
        {
            LoadMapFile(*it);
        }
    }

    std::map<std::wstring, std::wstring>::iterator it = m_map.find(clsid);

    return it != m_map.end() ? it->second : L"";
}

void CComFileMap::LoadMapFile(const std::wstring& filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(x3::CLSID_ConfigXmlFile);
    ASSERT(pIFFile.IsNotNull());

    pIFFile->SetFileName(filename.c_str());
    pIFFile->SetRootName(L"commap");

    Cx_Ptr obj;
    Cx_ConfigSection root(pIFFile->GetData()->GetSection(obj, L"", false));

    for (int i = 0; ; i++)
    {
        Cx_ConfigSection item(root.GetSectionByIndex(obj, L"item", i));
        std::wstring clsid(item->GetString(L"classid"));
        std::wstring file(item->GetString(L"filename"));

        if (clsid.empty() || file.empty())
        {
            break;
        }
        if (m_map.find(clsid) == m_map.end())
        {
            m_map[clsid] = file;
        }
        else
        {
            X3LOG_WARNING2(L"The classid is already registered", clsid);
        }
    }
}

// CComModules
//

CComModules::CComModules()
{
}

CComModules::~CComModules()
{
    Free();
}

void CComModules::Free()
{
    for (std::vector<HMODULE>::iterator it = m_modules.begin();
        it != m_modules.end(); ++it)
    {
        FreeLibrary(*it);
    }
    m_modules.clear();
}

HMODULE CComModules::GetModule(const std::wstring& filename)
{
    const wchar_t* name = PathFindFileNameW(filename.c_str());
    HMODULE hmod = GetModuleHandleW(name);

    if (NULL == hmod)
    {
        Cx_Interface<Ix_PluginDelayLoad> pIFLoader(x3::CLSID_PluginDelayLoad);
        SafeCall(pIFLoader, LoadDelayedPlugin(filename));

        hmod = GetModuleHandleW(name);
    }
    if (NULL == hmod)
    {
        hmod = x3LoadLibrary(filename.c_str());
        if (NULL == hmod)
        {
            DWORD errcode = GetLastError();
            X3LOG_WARNING2(L"Fail to load module.", 
                x3::GetSystemErrorString(errcode) << L", " << filename);
        }
        else
        {
            m_modules.push_back(hmod);
        }
    }

    return hmod;
}
