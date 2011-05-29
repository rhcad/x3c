//! \file X3Portability.h
//! \brief Declare portability functions.

#ifndef X3C_PORTABILITY_H
#define X3C_PORTABILITY_H

#if defined(_WIN32)
#include "../Portability/x3win.h"
#else
#include "../Portability/x3unix.h"
#endif // _WIN32

#ifndef NOSTDIO
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
