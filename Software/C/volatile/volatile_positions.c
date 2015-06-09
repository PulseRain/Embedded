volatile unsigned int gVar1 = 0xABCD1234;
volatile unsigned int gVar2 = 0xDDDD7777;
unsigned int gVar3 = 0xCCCC6666;
unsigned int gVar4 = 0xDDDD4444;
unsigned int gVar5 = 0x55555555;

unsigned int gVar6 = 0x66666666;
unsigned int gVar7 = 0x77777777;


    typedef unsigned int    U32;
    typedef unsigned short  U16;
    typedef unsigned char   U8;

#define BUSY_FLAG (1 << 0)


typedef struct {
    U32 data1;
    U32 data2;
    U32 data3;
}REG_DATA;

#define DATA_BUFFER 0xABCD0008


int main()
{
    volatile unsigned int *p1 = &gVar1;  
    unsigned int volatile *p2 = &gVar2;
    unsigned int* volatile p3 = &gVar3;
    
    const volatile unsigned int *p4 = &gVar4;  
    
    volatile unsigned int * const p5 = (unsigned int*) 0x12345678; //&gVar5;  
    
    const unsigned int data = 333;
    
    const unsigned int* p6 = &gVar6;
    unsigned int* const p7 = &gVar7;
       
    
    unsigned int k = 0;
    
    const volatile U32 *p;
    volatile U32 *pp;
    
    U32 data1, data2, data3;
    
    volatile U32* const REG_CONTROL = (U32*) 0xABCD0000;
    volatile U32* const REG_STATUS  = (U32*) 0xABCD0004;
    
    
    p = (U32*)DATA_BUFFER;
    pp = (U32*)DATA_BUFFER;
    
    
    //REG_CONTROL = 0x12345678;
    
    data1 = *p++;
    data2 = *p++;
    data3 = *p++;
    
    data3 = *pp++;
    (*pp) = 0;
    //(*p) = 0;
    
    (*REG_CONTROL) = 0x12345678;
    
    while((*REG_STATUS) & BUSY_FLAG);
    
    
    
    
    
    
    //data = 111;
    
    
    
    
    p4 = 0;
    //*p4 = 0;
    
   // p5 = 0;
   (*p5) = 0;
   
   p6 = 0;
   //(*p6) = 0;
   
   // p7 = 0; 
   (*p7) = 0;
    
    
    k += (*p1);
    k += (*p2);
    k += (*p3);
    k += (*p4);
    k += (*p5);
    k += (*p6);
    k += (*p7);
    
    
        
    return k;
} // End of main()

