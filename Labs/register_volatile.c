unsigned int gVar = 0xABCD1234;

int main()
{
    register volatile unsigned int *p = &gVar;
    unsigned int k = 0;

    k += (*p);
    k += (*p);
    
    return k;
} // End of main()
