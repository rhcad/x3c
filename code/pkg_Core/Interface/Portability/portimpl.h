#ifndef X3_PORTABILITY_IMPL_H
#define X3_PORTABILITY_IMPL_H

#if defined (__GNUC__)    // GCC
#if defined (__linux__)
#include "../Portability/linuximpl.h"
#elif defined (__MACOS__)
#include "../Portability/macimpl.h"
#endif
#endif // __GNUC__

#endif // X3_PORTABILITY_IMPL_H
