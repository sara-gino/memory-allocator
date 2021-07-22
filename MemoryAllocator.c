#include "MemoryAllocator.h"
#include <stdio.h>
#include <string.h>
struct MemoryAllocator MemoryAllocator;
struct MemoryAllocator* MemoryAllocator_init(void* memoryPool,size_t size){
    char* m_memoryPool=(char*)memoryPool;
    for (int i=0;i<size;i++){
        m_memoryPool[i]=(char)0;
    }
    int num=size-191;
    printf("%d",num);
    m_memoryPool[1]=(char)num;
    printf(" %c",(char)num);
    printf(" %d",(int)(char)num==65);
    MemoryAllocator.pointer=(void*)m_memoryPool;
    MemoryAllocator.size=size;
    return &MemoryAllocator;
}

void* MemoryAllocator_allocate(struct MemoryAllocator* allocator,size_t size){
    char* ptr=(char*)allocator->pointer;
    printf("%d ggg %d",ptr[1],ptr[0]);
    while(!((int)ptr[0]==0 && (int)ptr[1]>=size)){
        ptr=ptr+(((int)ptr[1])+2);
    }
    ptr[0]=(char)1;
    int old_val=(int)ptr[1];
    ptr[1]=(char)size;
    char *resulte = ptr + 2;
    if(old_val>size){
        ptr=ptr+(((int)ptr[1])+2);
        ptr[0]=(char)0;
        ptr[1]=(char)(old_val-size-2);
    }
    return allocator->pointer;
}

void MemoryAllocator_free(struct MemoryAllocator* allocator, void* ptr){
    char* pointer=(char*)allocator->pointer;
    while (pointer+2!=ptr){
        pointer=pointer+((int)pointer[1])+2;
    }
    pointer[0]=(char)0;
    char* next_pointer=pointer+(int)pointer[1]+2;
    if ((int)next_pointer[0]==0){
        pointer[1]=(char)((int)pointer[1]+(int)next_pointer[1]+2);
        next_pointer[1]=(char)0;
    }
}

size_t MemoryAllocator_optimize(struct MemoryAllocator* allocator){
    char* pointer=(char*)allocator->pointer;
    size_t arr_max=0;
    while ((int)pointer[0] != 0) {
        pointer = pointer + (int) pointer[1] + 2;
    }
    char* next_pointer = pointer + (int) pointer[1] + 2;
    while ((int)next_pointer[1]>0) {
        while ((int) next_pointer[0] == 0 &&(int)next_pointer[1]>0) {
            pointer[1] = (char)((int)pointer[1]+(int)next_pointer[1]+2);
            next_pointer[1] = (char) 0;
            next_pointer = next_pointer + (int) next_pointer[1] + 2;
        }
        if ((size_t)pointer[1] > arr_max) {
            arr_max = (size_t)pointer[1];
        }
        pointer = next_pointer;
        while ((int)pointer[0] != 0) {
            pointer = pointer + (int) pointer[1] + 2;
        }
        next_pointer = pointer + (int) pointer[1] + 2;
    }
    if ((size_t)pointer[1] > arr_max) {
        arr_max = (size_t)pointer[1];
    }
    return arr_max;
}
