#ifndef MEMPOOL
#define MEMPOOL

#include <stdlib.h>

typedef struct
{
    unsigned int num_blocks;
    unsigned int block_size;
    unsigned int num_free_blocks;
    unsigned int num_initialized_blocks;
    unsigned char *pool_start;
    unsigned char *next;
} pool;

/// @brief Creates a memory pool with the given block size and number of blocks.
/// @param block_size The size of each block in the pool.
/// @param num_blocks The number of blocks in the pool.
/// @return The newly created pool.
extern pool create_pool(size_t block_size, unsigned int num_blocks);

/// @brief Deallocates the heap memory used by the pool.
/// @param p The pool to destroy.
extern void destroy_pool(pool *p);

/// @brief Gets the address of the block at the given index.
/// @param p The pool to get the address from.
/// @param index The index of the block to get the address of.
/// @return The address of the block at the given index.
extern unsigned char *addr_from_index(pool *p, unsigned int index);

/// @brief Gets the index of the block at the given address.
/// @param p The pool to get the index from.
/// @param addr The address of the block to get the index of.
/// @return The index of the block at the given address.
extern unsigned int index_from_addr(pool *p, unsigned char *addr);

/// @brief Allocates a block from the pool.
/// @param p The pool to allocate from.
/// @return The address of the allocated block.
/// @note This function will return NULL if the pool is full.
/// @warning This function returns a void pointer because we don't know what
/// type of data the pool will be used for. Don't forget to cast the return appropriately.
extern void *alloc(pool *p);

/// @brief Deallocates a block from the pool.
/// @param p The pool to deallocate from.
/// @param addr The address of the block to deallocate.
/// @warning This function assumes that the given address is valid.
extern void dealloc(pool *p, void *addr);
#endif