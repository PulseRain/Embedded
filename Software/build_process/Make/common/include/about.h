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
*   Header file for about.c
*   (Noted by C.Gu on 10/01/2011)
*
* References:
*
******************************************************************************/

#ifndef ABOUT_H
#define ABOUT_H
 
#include "common_type.h"
 
#define ABOUT_SIGNATURE_LENGTH          256

extern U32 about(U32 about_CRC32);
extern void logo_print();

#endif
