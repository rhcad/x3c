/*! \file PluginInc.h
 *  \brief Include frequently-used files for plugin project.
 *  \author Zhang Yun Gui, X3 C++ PluginFramework
 *  \date   2011.06.30
 */
#ifndef X3PLUGIN_INC_H
#define X3PLUGIN_INC_H

#include <UtilFunc/X3Portability.h>

#ifndef NO_VECFUNC
#include <UtilFunc/vecfunc.h>   // STL master include file and functions
#endif
#ifndef NO_SAFECALL
#include <UtilFunc/SafeCall.h>  // SafeCall and InterfaceSafeCall
#endif
#ifndef NO_DEBUGR
#include <Log/DebugR.h>         // ASSERT, VERIFY and ASSERT_MESSAGE
#endif
#ifndef NO_LOGHELPER
#include <Log/LogHelper.h>      // X3LOG_WARNING, X3LogGroup ...
#endif
#ifndef NO_CLASSMACRO
#include <Module/XClassMacro.h> // X3BEGIN_CLASS_DECLARE
#endif

#endif // X3PLUGIN_INC_H