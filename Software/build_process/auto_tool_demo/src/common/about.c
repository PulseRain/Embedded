/******************************************************************************
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 3
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*
* Remarks:
*   To generate signature for version number and copyright claim
*   (Noted by C.Gu on 10/01/2011)
*
* References:
*
******************************************************************************/

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