#include "mem_pool.h"

pool create_pool(size_t block_size, unsigned int num_blocks)
{
    pool new_pool = {
        .num_blocks = num_blocks,
        .block_size = block_size,
        .num_free_blocks = num_blocks,
        .num_initialized_blocks = 0,
        .pool_start = malloc(block_size * num_blocks),
        .next = new_pool.pool_start,
    };

    return new_pool;
}

extern void destroy_pool(pool *p)
{
    free(p->pool_start);
    p->pool_start = NULL;
}

unsigned char *addr_from_index(pool *p, unsigned int index)
{
    return p->pool_start + (index * p->block_size);
}

unsigned int index_from_addr(pool *p, unsigned char *addr)
{
    return (unsigned int)(addr - p->pool_start) / p->block_size;
}

void *alloc(pool *p)
{
    // If the pool is not full, initialize the next block.
    if (p->num_initialized_blocks < p->num_blocks)
    {
        unsigned int *ptr = (unsigned int *)addr_from_index(p, p->num_initialized_blocks);
        *ptr = p->num_initialized_blocks + 1;
        p->num_initialized_blocks++;
    }

    // If there are free blocks, return the next free block.
    void *ret = NULL;
    if (p->num_free_blocks > 0)
    {
        ret = (void *)p->next;
        p->num_free_blocks--;
        // If there are more free blocks, set the next free block to the next block.
        if (p->num_free_blocks > 0)
            p->next = addr_from_index(p, *(unsigned int *)p->next);
        // If there are no more free blocks, set the next free block to NULL.
        else
            p->next = NULL;
    }
    return ret;
}

void dealloc(pool *p, void *ptr)
{
    // If there are no free blocks, set the next free block to the given block.
    if (p->next == NULL)
    {
        *(unsigned int *)ptr = index_from_addr(p, p->next);
        p->next = (unsigned char *)ptr;
    }
    // If there are free blocks, set the next free block to the given block
    // and set the next block to the previous next free block.
    else
    {
        *(unsigned int *)ptr = index_from_addr(p, p->next);
        p->next = (unsigned char *)ptr;
    }
    p->num_free_blocks++;
}