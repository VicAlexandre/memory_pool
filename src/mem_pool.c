#include "mem_pool.h"

Pool *create_pool(size_t block_size, uint16_t num_blocks)
{
    size_t total_size = sizeof(Pool) + block_size * num_blocks;

    Pool *new_pool = (Pool *)malloc(total_size);
    if (!new_pool)
        return NULL;

    new_pool->num_blocks = num_blocks;
    new_pool->block_size = block_size;
    new_pool->num_free_blocks = num_blocks;
    new_pool->num_initialized_blocks = 0;
    new_pool->pool_start = (unsigned char *)new_pool + sizeof(Pool);
    new_pool->next = (unsigned char *)new_pool + sizeof(Pool);

    return new_pool;
}

void destroy_pool(Pool *p)
{
    if (p != NULL)
        free(p);
}

static unsigned char *addr_from_index(Pool *p, uint16_t index)
{
    return p->pool_start + (index * p->block_size);
}

static uint16_t index_from_addr(Pool *p, unsigned char *addr)
{
    return (uint16_t)(addr - p->pool_start) / p->block_size;
}

void *alloc(Pool *p)
{
    // If the pool is not full, initialize the next block.
    if (p->num_initialized_blocks < p->num_blocks)
    {
        uint16_t *ptr = (uint16_t *)addr_from_index(p, p->num_initialized_blocks);
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
            p->next = addr_from_index(p, *(uint16_t *)p->next);
        // If there are no more free blocks, set the next free block to NULL.
        else
            p->next = NULL;
    }
    return ret;
}

void dealloc(Pool *p, void *ptr)
{
    if (ptr == NULL)
        return;

    // If there are no free blocks, set the next free block to the given block.
    // If there are free blocks, set the next free block to the given block
    // and set the next block to the previous next free block.

    if (p->next != NULL)
    {
        *(uint16_t *)ptr = index_from_addr(p, p->next);
        p->next = (unsigned char *)ptr;
    }
    else
    {
        *(uint16_t *)ptr = p->num_blocks;
        p->next = (unsigned char *)ptr;
    }
    p->num_free_blocks++;
}