#include "mem_pool.h"
#include <stdio.h>

// This is a simple test program to test the memory pool.
// Not meant to be a comprehensive test, only tests basic functionality.

typedef struct
{
    int a;
    int b;
} test_struct;

int main(void)
{
    Pool *p = create_pool(sizeof(test_struct), 10);
    test_struct *ptrs[10];

    for (int i = 0; i < 10; i++)
    {
        ptrs[i] = alloc(p);
        ptrs[i]->a = i;
        ptrs[i]->b = i * 2;
    }

    for (int i = 0; i < 10; i++)
    {
        printf("ptrs[%d]->a = %d\n", i, ptrs[i]->a);
        printf("ptrs[%d]->b = %d\n\n", i, ptrs[i]->b);
    }

    for (int i = 0; i < 10; i++)
    {
        dealloc(p, ptrs[i]);
    }

    destroy_pool(p);
    printf("First Test = Success.\n");

    Pool *p2 = create_pool(sizeof(test_struct), 100);
    test_struct *ptrs2[100];

    for (int i = 0; i < 100; i++)
    {
        ptrs2[i] = alloc(p2);
        ptrs2[i]->a = i;
        ptrs2[i]->b = i * 2;
    }
    test_struct *extra_ptr = alloc(p2);
    if (extra_ptr == NULL)
        printf("Second Test = Success.\n");
    else
        printf("Second Test = Failure.\n");

    for (int i = 0; i < 100; i++)
    {
        dealloc(p2, ptrs2[i]);
    }

    destroy_pool(p2);

    return 0;
}
