#ifndef ZMALLOC_H
#define ZMALLOC_H
#include <stdint.h>

// given an unsigned integer, size
// returns a pointer to a place in memory with at least size bytes
// will be 8-byte (double-word) aligned
// will return NULL if memory cannot be allocated or 0 is passed in
void *zmalloc(size_t size);

// deallocates memory allocated by zmalloc
void zfree(void *ptr);

// changes the size of the block that ptr points to
// possibly moving the memory to somewhere else
void *zrealloc(void *ptr, size_t size);

// allocates num * size bytes and initializes them to 0
void *zcalloc(size_t num, size_t size);

#ifdef DEBUG
// prints the memory usage and mapping to stdout
void zprint_memory(void);
#endif // DEBUG

// semi-private methods
// they shouldn't be needed in most cases except
// when the memory allocator needs to clean up
// after itself or be initialized multiple times

// function that initializes the memory
// right now it just uses system malloc
// to allocate a block of z_min_chunk_sizen bytes
void zmalloc_init(void);

// free any system memory that may have been allocated
// in zmalloc_init()
void zmalloc_cleanup(void);

// since everything needs to be double-word aligned the ZRegion
// struct (bookkeeping information for each block) should be 8 bytes
typedef struct ZRegion {
  uint32_t free;
  uint32_t size;
} ZRegion;

#endif // ZMALLOC_H

