#include <UtilFunc/PluginInc.h>
#include "ComFileMap.h"
#include <UtilFunc/ScanFiles.h>
#include <UtilFunc/RelToAbs.h>
#include <Xml/Ix_ConfigXml.h>
#include <Xml/Cx_ConfigSection.h>

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
        std::wstring path(x3::FileNameRelToAbs(L"config\\commap", false));

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

    Cx_ConfigSection root(pIFFile->GetData()->GetSection(L"", false));

    for (int i = 0; ; i++)
    {
        Cx_ConfigSection item(root.GetSectionByIndex(L"item", i));
        std::wstring clsid(item->GetString(L"classid"));
        std::wstring file(item->GetString(L"filename"));

        if (clsid.empty() || file.empty())
        {
            break;
        }
        m_map[clsid] = file;
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
}

HMODULE CComModules::GetModule(const std::wstring& filename)
{
    HMODULE hmod = GetModuleHandleW(PathFindFileNameW(filename.c_str()));

    if (NULL == hmod)
    {
    }

    return hmod;
}
