
/*

Copyright (C) 2007 Coolsoft Company. All rights reserved.

http://www.coolsoft-sd.com/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the
use of this software. 

Permission is granted to anyone to use this software for any purpose, including
commercial applications, and to alter it and redistribute it freely, subject to
the following restrictions: 

 * The origin of this software must not be misrepresented; you must not claim that
   you wrote the original software. If you use this software in a product, an
   acknowledgment in the product documentation would be appreciated but is not required.
 * Altered source versions must be plainly marked as such, and must not be misrepresented
   as being the original software. 
 * This notice may not be removed or altered from any source distribution. 

*/


#pragma once

#ifndef _MANAGED
	#include <string>
	using namespace std;

	#define CONST const
	#define CLASS class
	#define AS_PUBLIC
	#define NEW new
	#define NULLPTR NULL

	typedef wstring STRING;
	typedef const STRING& STRING_IN;
	typedef STRING& STRING_OUT;
	typedef const STRING& STRING_RET;
#else
	using namespace System;

	#define CONST
	#define CLASS ref class
	#define AS_PUBLIC public

	typedef System::String^ STRING;
	typedef STRING STRING_IN;
	typedef STRING% STRING_OUT;
	typedef STRING STRING_RET;
#endif