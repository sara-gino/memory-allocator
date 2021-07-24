
#ifndef MEMORY_ALLOCATION_SERVICE_MEMORYALLOCATOR_H
#define MEMORY_ALLOCATION_SERVICE_MEMORYALLOCATOR_H
#include <stddef.h>
struct MemoryAllocator{
    void* pointer;
    size_t size;
};
/* memoryPool is a ptr to an already-existing large memory
block */
struct MemoryAllocator * MemoryAllocator_init(void* memoryPool,size_t size);
/* Returns a ptr to the memoryPool */
//void* MemoryAllocator_release(MemoryAllocator* allocator);
void* MemoryAllocator_allocate(struct MemoryAllocator* allocator,
                               size_t size);
///* Merge the next adjacent block is free */
void MemoryAllocator_free(struct MemoryAllocator* allocator, void*
ptr);
///* Merges all adjacent free blocks, and returns the size of
//largest free block */
size_t MemoryAllocator_optimize(struct MemoryAllocator*
allocator);
void* MemoryAllocator_release(struct MemoryAllocator* allocator);

#endif //MEMORY_ALLOCATION_SERVICE_MEMORYALLOCATOR_H
