//! \file X3Portability.h
//! \brief Implement portability for linux and windows.

#ifndef X3C_PORTABILITY_H
#define X3C_PORTABILITY_H

#if defined (_MSC_VER)      // VC++

#include "../Portability/x3vc.h"

#elif defined (__GNUC__)    // GCC

#include "../Portability/portgcc.h"

#endif // _MSC_VER

#ifdef _NEED_STDIO
#include <stdio.h>
#include <stdarg.h>
#ifndef _STDIO_DEFINED
#define _STDIO_DEFINED
#endif
#endif
#include "func_s.h"

#endif // X3C_PORTABILITY_H
