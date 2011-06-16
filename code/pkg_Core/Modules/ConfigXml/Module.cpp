// Copyright 2008-2011 Zhang Yun Gui, rhcad@hotmail.com
// http://sourceforge.net/projects/x3c/

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

X3BEGIN_MODULE()
    X3_CLASS_ENTRY(X3CLS_ConfigXmlFile, Cx_ConfigXml)
    X3_CLASS_ENTRY(X3CLSID(), Cx_XmlSection)
X3END_MODULE_DLL()
