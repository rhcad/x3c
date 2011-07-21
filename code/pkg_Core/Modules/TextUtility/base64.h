
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

#include "ManagedExt.h"

#ifndef _MANAGED
typedef const unsigned char* BYTE_DATA_IN;
typedef unsigned char* BYTE_DATA_OUT;
#else
typedef array<Byte>^ BYTE_DATA_IN;
typedef array<Byte>^% BYTE_DATA_OUT;
#endif

// Encoding and decoding Base64 code
AS_PUBLIC CLASS Base64
{
public:

	// Encodes binary data to Base64 code
	// Returns size of encoded data.
	static int Encode(BYTE_DATA_IN inData,
		int dataLength,
		STRING_OUT outCode,
        wchar_t CHAR_63 = '+', wchar_t CHAR_64 = '/', wchar_t CHAR_PAD = '=');

	// Decodes Base64 code to binary data
	// Returns size of decoded data.
	static int Decode(STRING_IN inCode,
		int codeLength,
		BYTE_DATA_OUT outData,
        wchar_t CHAR_63 = '+', wchar_t CHAR_64 = '/', wchar_t CHAR_PAD = '=');

	// Returns maximum size of decoded data based on size of Base64 code.
	static int GetDataLength(int codeLength);

	// Returns maximum length of Base64 code based on size of uncoded data.
	static int GetCodeLength(int dataLength);

};
