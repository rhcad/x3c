// Implement portability functions.
// This file has included by XModuleImpl.h and XComCreator.h

#ifndef X3_PORTABILITY_IMPL_H
#define X3_PORTABILITY_IMPL_H

#if defined (__GNUC__)    // GCC
#if defined (__linux__)
#include "linuximpl.h"
#elif defined (MACOS) || defined (_MAC)
#include "macimpl.h"
#endif
#endif // __GNUC__

#include "pathstr.h"

#endif // X3_PORTABILITY_IMPL_H
