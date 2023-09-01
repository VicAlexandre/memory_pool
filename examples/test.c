#include "mem_pool.h"
#include <stdio.h>

// This is a simple test program to test the memory pool.

typedef struct
{
    int a;
    int b;
} test_struct;

int main(void)
{
    pool p = create_pool(sizeof(test_struct), 10);
    test_struct *ptrs[10];

    for (int i = 0; i < 10; i++)
    {
        ptrs[i] = alloc(&p);
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
        dealloc(&p, ptrs[i]);
    }

    destroy_pool(&p);
    printf("Success.\n");
    return 0;
}
