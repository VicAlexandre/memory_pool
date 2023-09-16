// A memory pool implementation based off of Ben Kenwright's article:
// Fast Efficient Fixed-Size Memory Pool: No Loops and No Overhead
// (http://www.thinkmind.org/index.php?view=article&articleid=computation_tools_2012_1_10_80006)
//
// Written by: Victor A. Miranda - GitHub: @VicAlexandre

#ifndef MEMPOOL
#define MEMPOOL

#include <stdlib.h>
#include <stdint.h>

typedef struct
{
    uint16_t num_blocks;
    uint16_t block_size;
    uint16_t num_free_blocks;
    uint16_t num_initialized_blocks;
    unsigned char *pool_start;
    unsigned char *next;
} Pool;

/// @brief Creates a memory pool with the given block size and number of
/// blocks and returns a pointer to it.
/// @param block_size The size of each block in the pool.
/// @param num_blocks The number of blocks in the pool.
/// @return A pointer to the newly created pool, or NULL if the allocation failed.
/// @note After creating a pool, it's not possible to resize it. The pool only supports
/// up to 2^16 - 1 blocks with a maximum block size of 2^16 - 1 bytes.
/// @warning As the pool is dynamically allocated, it's the caller's responsibility
/// to deallocate it when it's lifecycle is over.
Pool *create_pool(size_t block_size, uint16_t num_blocks);

/// @brief Deallocates the memory pool.
/// @param p A pointer to the pool to deallocate.
/// @note This function does nothing if the given pointer is NULL.
void destroy_pool(Pool *p);

/// @brief Allocates a block from the pool.
/// @param p The pool to allocate from.
/// @return The address of the allocated block, or NULL if the allocation failed.
/// @warning This function returns a void pointer because it's not possible to know the
/// type of data the pool will be used for. Don't forget to cast the return appropriately.
void *alloc(Pool *p);

/// @brief Deallocates a block from the pool.
/// @param p The pool to deallocate from.
/// @param addr The address of the block to deallocate.
/// @warning This function assumes that the given address is valid.
void dealloc(Pool *p, void *addr);
#endif