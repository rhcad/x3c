// x3c - C++ PluginFramework
#include <UtilFunc/PluginInc.h>
#include <Module/XModuleMacro.h>
#include <Module/XModuleImpl.h>

#include "Cx_ConfigXml.h"
#include "Cx_XmlSection.h"

#ifdef _XMLDOM_HELPERS_H
#include "XmlUtil/XmlUtil.cpp"
#else
#include "TinyXml/XmlUtil.cpp"
#endif

XBEGIN_DEFINE_MODULE()
    XDEFINE_CLASSMAP_ENTRY(x3::CLSID_ConfigXmlFile, Cx_ConfigXml)
    XDEFINE_CLASSMAP_ENTRY(CLSID_XmlSection, Cx_XmlSection)
XEND_DEFINE_MODULE_DLL()
