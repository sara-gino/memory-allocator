#include <stdio.h>
#include <stddef.h>
#include "MemoryAllocator.h"
int main() {
    char memoryPool[256];
//    printf("sara");
    struct MemoryAllocator* a;
    a=MemoryAllocator_init(memoryPool,(size_t)256);
    void *f = MemoryAllocator_allocate(a, (size_t) 10);
    char* m_f=(char*)f;
    printf("  %d %d %d %d ",(int)m_f[0],(int)m_f[1],(int)m_f[((int)m_f[1])+2],(int)m_f[((int)m_f[1])+3]);
    void *f2= MemoryAllocator_allocate(a, (size_t) 1);
    char* m_f2=(char*)f2;
    printf("  %d %d %d %d %d %d ",(int)m_f2[0],(int)m_f2[1],(int)m_f2[((int)m_f2[1])+2],(int)m_f2[((int)m_f2[1])+3],(int)m_f2[((int)m_f2[1])+3+2],(int)m_f2[((int)m_f2[1])+3+3]);
//    MemoryAllocator_free(a,m_f2+2);
    printf("  %d %d %d %d %d %d ",(int)m_f2[0],(int)m_f2[1],(int)m_f2[((int)m_f2[1])+2],(int)m_f2[((int)m_f2[1])+3],(int)m_f2[((int)m_f2[1])+3+2],(int)m_f2[((int)m_f2[1])+3+3]);
    MemoryAllocator_free(a,m_f2+14);
    size_t e;
    printf("  %d %d %d %d %d %d ",(int)m_f2[0],(int)m_f2[1],(int)m_f2[((int)m_f2[1])+2],(int)m_f2[((int)m_f2[1])+3],(int)m_f2[((int)m_f2[1])+3+2],(int)m_f2[((int)m_f2[1])+3+3]);
    e=MemoryAllocator_optimize(a);
    printf("  %d %d %d %d %d %d ",(int)m_f2[0],(int)m_f2[1],(int)m_f2[((int)m_f2[1])+2],(int)m_f2[((int)m_f2[1])+3],(int)m_f2[((int)m_f2[1])+3+2],(int)m_f2[((int)m_f2[1])+3+3]);
    printf("max free block: %zu",e);

};