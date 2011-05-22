//! \file X3Portability.h
//! \brief Declare portability functions.

#ifndef X3C_PORTABILITY_H
#define X3C_PORTABILITY_H

#if defined(_WIN32)
#include "../Portability/x3vc.h"
#else
#include "../Portability/portgcc.h"
#endif // _WIN32

#ifdef _NEED_STDIO
#include <stdio.h>
#include <stdarg.h>
#ifndef _STDIO_DEFINED
#define _STDIO_DEFINED
#endif
#endif
#if !defined(_MSC_VER) || _MSC_VER < 1400   // not VC8
#include "func_s.h"
#endif

#endif // X3C_PORTABILITY_H
