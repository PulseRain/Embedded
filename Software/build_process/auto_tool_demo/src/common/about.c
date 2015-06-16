/*
//===========================================================================
// Copyright (c) : Pulserain Technology, LLC. 2015
//===========================================================================
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
*/

#include "common_type.h"
#include "debug.h"
#include "about.h"
#include "CRC32.h"

#define VERSION_STR(s) VERSION_STR_(s)
#define VERSION_STR_(s) #s

const U8 about_signature[ABOUT_SIGNATURE_LENGTH] = \
  "\n===================================================================\n"\
  VERSION_STR(PRODUCT_NAME)"\n"\
  "Version "VERSION_STR(VMAJOR)"."VERSION_STR(VMINOR)"\n"\
  "Copyright (c) 2xxx ... Corporation. All Rights Reserved.\n"\
  "===================================================================\n\n";


/*
//-----------------------------------------------------------------------------
// about()
//
// Parameters:
//		about_CRC32  : CRC32 of about signature
//
// Return Values:
//		CRC32 of the about_signature[]
//
// Remarks:
//		print out the version number and copyright claim
//      Two macros : VMAJOR and VMINOR should be defined in the Makefile as
//      compile option, such as -DVMAJOR=1 -DVMINOR=3
//-----------------------------------------------------------------------------
*/

U32 about(U32 about_CRC32)
{
    while(generate_CRC32(about_signature, ABOUT_SIGNATURE_LENGTH)!= about_CRC32);
       
    CONSOLE_PRINT("%s\n", about_signature);
    
    return generate_CRC32(about_signature, ABOUT_SIGNATURE_LENGTH);
} // End of  about()

/*
//-----------------------------------------------------------------------------
// logo_print()
//
// Parameters:
//		None
//
// Return Values:
//		None
//
// Remarks:
//		print out Logo pattern
//-----------------------------------------------------------------------------
*/

void logo_print()
{
    CONSOLE_PRINT("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
	CONSOLE_PRINT("$$                             $$\n");
	CONSOLE_PRINT("$$$$$                       $$$$$\n");
	CONSOLE_PRINT("$$$$$$$$$$$$$$     $$$$$$$$$$$$$$\n");
	CONSOLE_PRINT("$$$$$                       $$$$$\n");
	CONSOLE_PRINT("$$                             $$\n");
    CONSOLE_PRINT("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
} // End of logo_print()