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
    
    printf ("sizeof(STRUCT_PACKED) = %d \n", sizeof(STRUCT_PACKED));
    printf ("sizeof(STRUCT_NOT_PACKED) = %d \n", sizeof(STRUCT_NOT_PACKED));
    
    printf ("sizeof(MANUAL_PADDING) = %d \n", sizeof(STRUCT_MANUAL_PADDING));
    
    printf ("field_offset STRUCT_PACKED b = %d\n", FIELD_OFFSET(STRUCT_PACKED, b));
    printf ("field_offset STRUCT_NOT_PACKED b = %d\n", FIELD_OFFSET(STRUCT_NOT_PACKED, b));
    printf ("field_offset STRUCT_MANUAL_PADDING b = %d\n", FIELD_OFFSET(STRUCT_MANUAL_PADDING, b));
    
    
    
    
    
    
    printf ("type alignment STRUCT_PACKED  = %d\n", TYPE_ALIGNMENT(STRUCT_PACKED));
    printf ("type alignment STRUCT_NOT_PACKED  = %d\n", TYPE_ALIGNMENT(STRUCT_NOT_PACKED));
    printf ("type alignment STRUCT_MANUAL_PADDING  = %d\n", TYPE_ALIGNMENT(STRUCT_MANUAL_PADDING));
    
    printf ("sizeof(long) = %d\n", sizeof(long));
    
}
