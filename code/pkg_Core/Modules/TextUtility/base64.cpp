
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

#include "base64.h"

// Encodes binary data to Base64 code
// Returns size of encoded data.
int Base64::Encode(BYTE_DATA_IN inData,
				   int dataLength,
				   STRING_OUT outCode,
                   wchar_t CHAR_63, wchar_t CHAR_64, wchar_t CHAR_PAD)
{

#ifndef _MANAGED

	STRING result;

	// output buffer which holds code during conversation
	int len = GetCodeLength( dataLength );
	wchar_t* out = new wchar_t[ len ];

	// charachers used by Base64
	static const wchar_t alph[] =
	{
		'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
		'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
		'0','1','2','3','4','5','6','7','8','9',CHAR_63,CHAR_64
	};

	// mask - first six bits
	const int mask = 0x3F;

	// used as temp 24-bits buffer
	union
	{
		unsigned char bytes[ 4 ];
		unsigned int block;
	} buffer;

	// coversation is done by taking three bytes at time of input data int temp
	// then four six-bits values are extracted, converted to base64 characters
	// and at the end they are written to output buffer
	for( int i = 0, j = 0, left = dataLength; i < dataLength; i += 3, j += 4, left -= 3 )
	{
		//------------------------
		// filling temp buffer

		// get first byte and puts it at MSB position in temp buffer
		buffer.bytes[ 2 ] = inData[ i ];

		// more data left?
		if( left > 1 )
		{
			// get second byte and puts it at middle position in temp buffer
			buffer.bytes[ 1 ] = inData[ i + 1 ];
			// more data left?
			if( left > 2 )
				// get third byte and puts it at LSB position in temp buffer
				buffer.bytes[ 0 ] = inData[ i + 2 ];
			else
				// zero-padding of input data (last bytes)
				buffer.bytes[ 0 ] = 0;
		}
		else
		{
			// zero-padding of input data (last two bytes)
			buffer.bytes[ 1 ] = 0;
			buffer.bytes[ 0 ] = 0;
		}

		//------------------------
		// constructing code from temp buffer
		// and putting it in output buffer

		// extract first and second six-bit value from temp buffer
		// and convert is to base64 character
		out[ j ] = alph[ ( buffer.block >> 18 ) & mask ];
		out[ j + 1 ] = alph[ ( buffer.block >> 12 ) & mask ];
		// more data left?
		if( left > 1 )
		{
			// extract third six-bit value from temp buffer
			// and convert it to base64 character
			out[ j + 2 ] = alph[ ( buffer.block >> 6 ) & mask ];
			// more data left?
			if( left > 2 )
				// extract forth six-bit value from temp buffer
				// and convert it to base64 character
				out[ j + 3 ] = alph[ buffer.block & mask ];
			else
				// pad output code
				out[ j + 3 ] = CHAR_PAD;
		}
		else
		{
			// pad output code
			out[ j + 2 ] = CHAR_PAD;
			out[ j + 3 ] = CHAR_PAD;
		}
	}

	outCode.resize(0);
	outCode.append( out, len );
	delete[] out;
	return len;

#else

	// encode
	outCode = System::Convert::ToBase64String( inData );

	// replace character if they are not standard
	if( CHAR_63 != '+' )
		outCode = outCode->Replace( '+', CHAR_63 );
	if( CHAR_64 != '/' )
		outCode = outCode->Replace( '/', CHAR_64 );
	if( CHAR_PAD != '=' )
		outCode = outCode->Replace( '=', CHAR_PAD );

	return outCode->Length;

#endif
}

// Decodes Base64 code to binary data
// Returns size of decoded data.
int Base64::Decode(STRING_IN inCode,
				   int codeLength,
				   BYTE_DATA_OUT outData,
                   wchar_t CHAR_63, wchar_t CHAR_64, wchar_t CHAR_PAD)
{

#ifndef _MANAGED

	// used as temp 24-bits buffer
	union
	{
		unsigned char bytes[ 4 ];
		unsigned int block;
	} buffer;
	buffer.block = 0;

	// number of decoded bytes
	int j = 0;

	for( int i = 0; i < codeLength; i++ )
	{
		// position in temp buffer
		int m = i % 4;

		wchar_t x = inCode[ i ];
		int val = 0;

		// converts base64 character to six-bit value
		if( x >= 'A' && x <= 'Z' )
			val = x - 'A';
		else if( x >= 'a' && x <= 'z' )
			val = x - 'a' + 'Z' - 'A' + 1;
		else if( x >= '0' && x <= '9' )
			val = x - '0' + ( 'Z' - 'A' + 1 ) * 2;
		else if( x == CHAR_63 )
			val = 62;
		else if( x == CHAR_64 )
			val = 63;

		// padding chars are not decoded and written to output buffer
		if( x != CHAR_PAD )
			buffer.block |= val << ( 3 - m ) * 6;
		else
			m--;

		// temp buffer is full or end of code is reached
		// flushing temp buffer
		if( m == 3 || x == CHAR_PAD )
		{
			// writes byte from temp buffer (combined from two six-bit values) to output buffer
			outData[ j++ ] = buffer.bytes[ 2 ];
			// more data left?
			if( x != CHAR_PAD || m > 1 )
			{
				// writes byte from temp buffer (combined from two six-bit values) to output buffer
				outData[ j++ ] = buffer.bytes[ 1 ];
				// more data left?
				if( x != CHAR_PAD || m > 2 )
					// writes byte from temp buffer (combined from two six-bit values) to output buffer
					outData[ j++ ] = buffer.bytes[ 0 ];
			}

			// restarts temp buffer
			buffer.block = 0;
		}

		// when padding char is reached it is the end of code
		if( x == CHAR_PAD )
			break;
	}

	return j;

#else

	// reverse changes of character before decoding data
	if( CHAR_63 != '+' )
		inCode = inCode->Replace( CHAR_63, '+' );
	if( CHAR_64 != '/' )
		inCode = inCode->Replace( CHAR_64, '/' );
	if( CHAR_PAD != '=' )
		inCode = inCode->Replace( CHAR_PAD, '=' );

	// decode
	outData = System::Convert::FromBase64String( inCode );
	return inCode->Length;

#endif
}

// Returns maximum size of decoded data based on size of Base64 code.
int Base64::GetDataLength(int codeLength)
{
	return codeLength - codeLength / 4;
}

// Returns maximum length of Base64 code based on size of uncoded data.
int Base64::GetCodeLength(int dataLength)
{
	int len = dataLength + dataLength / 3 + (int)( dataLength % 3 != 0 );

	// output code size must be multiple of 4 bytes
	if( len % 4 )
		len += 4 - len % 4;

	return len;
}
