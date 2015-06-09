#include "stdio.h"

unsigned int gVar = 0xABCD1234;

int main()
{
    int i;
    volatile unsigned int *p = &gVar;
    unsigned int k = 0;
    
    
    for (i = 0; i < 100; ++i) {
        k += (*p);
    }
    
    
    
        
    return k;
} // End of main()

