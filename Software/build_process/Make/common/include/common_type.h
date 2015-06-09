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
*   Common header file for various type definition. 
*   (Noted by C.Gu on 03/25/2011)
*
* References:
*  [1] Cx51 Compiler User's Guide, Keil Software, 09/2001
******************************************************************************/


#ifndef COMMON_TYPE_H
#define COMMON_TYPE_H

#include "debug.h"

#if defined (KEIL_C51)

    typedef unsigned long int   U32;
    typedef unsigned short      U16;
    typedef unsigned char       U8;
        
    
    // Most 8051 variants are 8 bit CPU with a little endian bias. After all, 8051
    // is from Intel who is in the little endian camp. 
    // But Keil C51 compilier is treating 16 bit data as big endian (Ref [1]) !!!
    // (Noted by C.Gu on 04/03/2011)
    #define KEIL_16BIT(x) ((((x) << 8) & 0xFF00) | (((x) >> 8) & 0xFF))
    #define KEIL_32BIT(x) ((((x) << 24) & 0xFF000000) | (((x) >> 24) & 0x000000FF) | (((x) >> 8) & 0x0000FF00) | (((x) << 8) & 0x00FF0000) )

#else
    
    #define KEIL_16BIT(x)  (x)
    #define KEIL_32BIT(x)  (x)
    
    typedef long long       U64;
    typedef unsigned int    U32;
    typedef unsigned short  U16;
    typedef unsigned char   U8;

    C_ASSERT(sizeof(U64) == 8);

#endif

C_ASSERT(sizeof(U32) == 4);
C_ASSERT(sizeof(U16) == 2);
C_ASSERT(sizeof(U8) == 1);

     
#if defined (__GNUC__)              
    #define PACKED __attribute__((packed))
#endif


#ifndef PACKED
    #define PACKED
#endif


// define function return value

#define DEFAULT_ERROR 1
#define SUCCESS		  0

#endif
