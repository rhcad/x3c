// Implement portability functions.
// This file has included by XModuleImpl.h and XComCreator.h

#ifndef X3_PORTABILITY_IMPL_H
#define X3_PORTABILITY_IMPL_H

#if defined (_WIN32)
    #include "Portability/win32impl.h"
#else
    #include "Portability/pathstr.h"
    #if defined (__linux__)
    #include "Portability/linuximpl.h"
    #elif defined (MACOS) || defined (_MAC)
    #include "Portability/macimpl.h"
    #endif
#endif // _WIN32

#endif // X3_PORTABILITY_IMPL_H
