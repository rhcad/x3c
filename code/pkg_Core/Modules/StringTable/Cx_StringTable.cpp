// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include "Cx_StringTable.h"
#include <UtilFunc/ScanFiles.h>
#include <Xml/Ix_ConfigXml.h>
#include <Xml/Cx_ConfigSection.h>
#include <UtilFunc/RelToAbs.h>
#include <PluginManager/Ix_AppWorkPath.h>

Cx_StringTable::Cx_StringTable()
    : m_loaded(false)
{
}

Cx_StringTable::~Cx_StringTable()
{
}

std::wstring Cx_StringTable::GetValue(const std::wstring& module, 
                                      const std::wstring& id, bool* hasvalue)
{
    std::wstring value;

    GetValue(value, module, id);
    if (hasvalue)
    {
        *hasvalue = !value.empty();
    }
    if (value.empty())
    {
        X3LOG_WARNING2(L"@StringTable:IDS_NO_STRVALUE", module + L":" + id);
    }

    return value;
}

bool Cx_StringTable::GetValue(std::wstring& value, const std::wstring& name, 
    std::wstring& module, std::wstring& id)
{
    if (name.size() > 1 && L'@' == name[0] &&
        wcschr(name.c_str(), L':') != NULL)
    {
        const wchar_t* p = wcschr(name.c_str(), L':');

        module = std::wstring(name.c_str() + 1, (size_t)(p - name.c_str() - 1));
        id = p + 1;

        return GetValue(value, module, id);
    }

    return false;
}

static void ReplaceLf(std::wstring& text)
{
    for (int i = static_cast<int>(text.size()) - 1; i > 0; --i)
    {
        wchar_t c = text[i];
        if (L'\\' == text[i - 1] && (L'n' == c || L'r' == c || L't' == c))
        {
            switch (c)
            {
                case L'n': text[i - 1] = L'\n'; break;
                case L'r': text[i - 1] = L'\r'; break;
                case L't': text[i - 1] = L'\t'; break;
            }
            text.erase(i, 1);
        }
    }
}

bool Cx_StringTable::GetValue(std::wstring& value, 
    const std::wstring& module, const std::wstring& id)
{
    if (!m_loaded)
    {
        LoadFiles(x3::GetTranslationsPath(L"strings"));
        LoadFiles(x3::RelToAbsWithPlugin(L"../translations/strings", false));
    }

    IT_ITEM it = Find(module);

    value.resize(0);
    if (it != m_groups.end())
    {
        Cx_ConfigSection group(it->group);
        ASSERT(group.IsNotNull());

        Cx_ConfigSection sec(group.GetSection(L"string", L"id", id.c_str(), false));

        value = sec->GetString(L"value");
        ReplaceLf(value);
    }

    return !value.empty();
}

long Cx_StringTable::LoadFiles(const std::wstring& path)
{
    if (path.empty())
    {
        return 0;
    }

    long count = 0;
    std::vector<std::wstring> files;
    x3::CScanFilesByExtension scaner(&files, L".xml");

    x3::ScanFiles(&scaner, path.c_str(), false);
    m_loaded = true;

    std::vector<std::wstring>::const_iterator it = files.begin();
    for (; it != files.end(); ++it)
    {
        if (RegisterFile(*it) > 0)
        {
            count++;
        }
    }
    
    if (0 == count && m_groups.empty())
    {
        X3LOG_INFO2(L"@StringTable:IDS_NO_STRFILE", path);
    }

    return count;
}

long Cx_StringTable::RegisterFile(const std::wstring& filename)
{
    Cx_Interface<Ix_ConfigXml> pIFFile(x3::CLSID_ConfigXmlFile);
    if (pIFFile.IsNull())
    {
        return 0;
    }

    pIFFile->SetFileName(filename.c_str());
    X3LOG_DEBUG2(L"@StringTable:IDS_LOAD_STRFILE", PathFindFileNameW(filename.c_str()));

    long count = 0;
    for (int i = 0; i < 99; i++)
    {
        Cx_ConfigSection sec (pIFFile->GetData()->GetSectionByIndex(NULL, L"module", i));
        ITEM item;

        item.file = pIFFile->GetData();
        item.group = sec;
        item.module = sec->GetString(L"name");
        ASSERT(item.group && item.file);

        if (item.module.empty())
            break;

        if (Find(item.module) == m_groups.end())
        {
            m_groups.push_back(item);
            count++;
        }
        else
        {
            X3LOG_WARNING2(L"@StringTable:IDS_IGNORE_STRGROUP", item.module);
        }
    }

    return count;
}
