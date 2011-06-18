/*! \file Ix_UIConfig.h
 *  \brief Define UI config options interface: Ix_UIConfig
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2010.11.2
 */
#ifndef X3_APPUI_IUICONFIG_H_
#define X3_APPUI_IUICONFIG_H_

#include <Xml/Cx_ConfigSection.h>

X3CLSID_DEFINE(CLSID_UIConfig, "4472ba6d-d833-40b9-899f-edc017ec9166");

//! UI config options interface
/*!
    \interface Ix_UIConfig
    \ingroup _GROUP_APPUI_
    \see CLSID_UIConfig
*/
class Ix_UIConfig
{
public:
    virtual ~Ix_UIConfig() {}

    //! Return UI config data object, not null.
    virtual Ix_ConfigData* GetUIConfig() = 0;

    //! Return a config node object of the specified name.
    virtual Cx_ConfigSection GetUISection(const wchar_t* name) = 0;

    //! Save UI config data if modified.
    virtual bool Save() = 0;
};

#endif // X3_APPUI_IUICONFIG_H_
