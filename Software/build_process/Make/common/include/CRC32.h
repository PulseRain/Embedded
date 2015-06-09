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
*   Header file for CRC32.c
*   (Noted by C.Gu on 10/01/2011)
*
* References:
*
******************************************************************************/

#ifndef CRC32_H
#define CRC32_H

#include "common_type.h"

extern U32 generate_CRC32(const U8 data[], U32 length);

#endif
