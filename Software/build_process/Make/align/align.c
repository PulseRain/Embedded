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


#include "stdio.h"
#include "align.h"


typedef struct {
    U8 a;
    U32 b;
    U16 c;
} PACKED STRUCT_PACKED;

typedef struct {
    U8 a;
    U32 b;
    U16 c;
} STRUCT_NOT_PACKED;



typedef struct {
    U8 a;
    U8 a_padding[sizeof(int) - sizeof(U8)];
    U32 b;
    U8 b_padding[sizeof(int) - sizeof(U32)];
    U16 c;
    U8 c_padding[sizeof(int)-sizeof(U16)];
} STRUCT_MANUAL_PADDING;


        
C_ASSERT(sizeof(STRUCT_PACKED) == 7);
C_ASSERT(sizeof(STRUCT_NOT_PACKED) == 12);


C_ASSERT(TYPE_ALIGNMENT(STRUCT_PACKED) == 1);
C_ASSERT(TYPE_ALIGNMENT(STRUCT_NOT_PACKED) == 4);



void alignment_test()
{
    
    printf ("sizeof(STRUCT_PACKED) = %d \n", (int)sizeof(STRUCT_PACKED));
    printf ("sizeof(STRUCT_NOT_PACKED) = %d \n", (int)sizeof(STRUCT_NOT_PACKED));
    
    printf ("sizeof(MANUAL_PADDING) = %d \n", (int)sizeof(STRUCT_MANUAL_PADDING));
    
    printf ("field_offset STRUCT_PACKED b = %d\n", (int)FIELD_OFFSET(STRUCT_PACKED, b));
    printf ("field_offset STRUCT_NOT_PACKED b = %d\n", (int)FIELD_OFFSET(STRUCT_NOT_PACKED, b));
    printf ("field_offset STRUCT_MANUAL_PADDING b = %d\n", (int)FIELD_OFFSET(STRUCT_MANUAL_PADDING, b));
    
    
    
    
    
    
    printf ("type alignment STRUCT_PACKED  = %d\n", (int)TYPE_ALIGNMENT(STRUCT_PACKED));
    printf ("type alignment STRUCT_NOT_PACKED  = %d\n", (int)TYPE_ALIGNMENT(STRUCT_NOT_PACKED));
    printf ("type alignment STRUCT_MANUAL_PADDING  = %d\n", (int)TYPE_ALIGNMENT(STRUCT_MANUAL_PADDING));
    
    printf ("sizeof(long) = %d\n", (int)sizeof(long));
    
}
