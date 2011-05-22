// Implement portability functions.
// This file has included by XModuleImpl.h and XComCreator.h

#ifndef X3_PORTABILITY_IMPL_H
#define X3_PORTABILITY_IMPL_H

#if !defined (_WIN32)
    #if defined (__linux__)
        #include "linuximpl.h"
    #elif defined (MACOS) || defined (_MAC)
        #include "macimpl.h"
    #endif
    #include "pathstr.h"
#endif // _WIN32

#endif // X3_PORTABILITY_IMPL_H
