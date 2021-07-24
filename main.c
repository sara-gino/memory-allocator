#include <stdio.h>
#include <stddef.h>
#include "MemoryAllocator.h"
int main() {
    unsigned char memoryPool[256];
    struct MemoryAllocator* memoryAllocator;
    size_t max_free;
    memoryAllocator=MemoryAllocator_init(memoryPool,(size_t)256);
    void *f = MemoryAllocator_allocate(memoryAllocator, (size_t) 10);
    memoryAllocator->pointer=MemoryAllocator_release(memoryAllocator);
    unsigned char* m_f=(unsigned char*)f;
    void *f2= MemoryAllocator_allocate(memoryAllocator, (size_t) 2);
    MemoryAllocator_free(memoryAllocator,f2);
    void* f1= MemoryAllocator_allocate(memoryAllocator, (size_t) 1);
    void* f10= MemoryAllocator_allocate(memoryAllocator, (size_t) 10);
    void* f30= MemoryAllocator_allocate(memoryAllocator, (size_t) 30);
    MemoryAllocator_free(memoryAllocator,f10);
    MemoryAllocator_free(memoryAllocator,f1);
    max_free=MemoryAllocator_optimize(memoryAllocator);
    printf("max free block: %zu",max_free);
};
