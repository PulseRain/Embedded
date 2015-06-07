#include <stdio.h>

typedef int (*T_FUNC_POINTER)(int, int);

int func_add (int a, int b)
{
    return a + b;
}

int func_sub (int a, int b)
{
    return a - b;
}

int func_add_sub (int mode, int a, int b)
{
    T_FUNC_POINTER func_table[2]={func_add, func_sub};
    return (*(func_table[mode]))(a, b);
}

int main()
{
    printf ("add = %d\n", func_add_sub(0, 6, 4));
    printf ("sub = %d\n", func_add_sub(1, 6, 4));   
}
