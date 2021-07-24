#include "MemoryAllocator.h"
struct MemoryAllocator MemoryAllocator;

struct MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size){
    unsigned char* m_memoryPool=(unsigned char*)memoryPool;
    for (int i=0;i<size;i++){
        m_memoryPool[i]=(unsigned char)0;
    }
    int num=size-2;
    m_memoryPool[1]=(unsigned char)num;
    MemoryAllocator.pointer=(void*)m_memoryPool;
    MemoryAllocator.size=size;
    return &MemoryAllocator;
}


void* MemoryAllocator_release(struct MemoryAllocator* allocator){
    unsigned char* m_memoryPool=(unsigned char*)allocator->pointer;
    for (int i=0;i<allocator->size;i++){
        m_memoryPool[i]=(unsigned char)0;
    }
    int num=allocator->size-2;
    m_memoryPool[1]=(unsigned char)num;
    return allocator->pointer;
}


void* MemoryAllocator_allocate(struct MemoryAllocator* allocator,size_t size){
    char* ptr=(char*)allocator->pointer;
    while(!((int)ptr[0]==0 && (int)ptr[1]>=size )){
        if((int)ptr[1]==0 ){
            return NULL;
        }
        ptr=ptr+(((int)ptr[1])+2);
    }
    ptr[0]=(char)1;
    int old_size=(int)ptr[1];
    ptr[1]=(char)size;
    char* resulte = ptr + 2;
    if(old_size>size){
        ptr=ptr+(((int)ptr[1])+2);
        ptr[0]=(char)0;
        ptr[1]=(char)(old_size-size-2);
    }
    return resulte;
}


void MemoryAllocator_free(struct MemoryAllocator* allocator, void* ptr){
    unsigned char* pointer=(unsigned char*)allocator->pointer;
    while (pointer+2!=ptr){
        pointer=pointer+((int)pointer[1])+2;
    }
    pointer[0]=(unsigned char)0;
    unsigned char* next_pointer=pointer+(int)pointer[1]+2;
    if ((int)next_pointer[0]==0&&(int)next_pointer[1]>0){
        pointer[1]=(unsigned char)((int)pointer[1]+(int)next_pointer[1]+2);
        next_pointer[1]=(unsigned char)0;
    }
}


size_t MemoryAllocator_optimize(struct MemoryAllocator* allocator){
    unsigned char* pointer=(unsigned char*)allocator->pointer;
    size_t free_max=0;
    while ((int)pointer[0] != 0) {
        pointer = pointer + (int) pointer[1] + 2;
    }
    unsigned char* next_pointer = pointer + (int) pointer[1] + 2;
    while ((int)next_pointer[1]>0) {
        while ((int) next_pointer[0] == 0&&(int)next_pointer[1]>0) {
            pointer[1] = (unsigned char)((int)pointer[1]+(int)next_pointer[1]+2);
            next_pointer[1] = (unsigned char) 0;
            next_pointer = next_pointer + (int) next_pointer[1] + 2;
        }
        if ((size_t)pointer[1] > free_max) {
            free_max = (size_t)pointer[1];
        }
        pointer = next_pointer;
        while ((int)pointer[0] != 0) {
            pointer = pointer + (int) pointer[1] + 2;
        }
        next_pointer = pointer + (int) pointer[1] + 2;
    }
    if ((size_t)pointer[1] > free_max) {
        free_max = (size_t)pointer[1];
    }
    return free_max;
}

