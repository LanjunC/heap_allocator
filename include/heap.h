
#include "list.h"

typedef struct Heap
{
    uint64_t start;
    uint64_t end;
    List *lists[LIST_COUNT];
} Heap;

void InitHeap(Heap *heap, void *p);
void *HeapMalloc(Heap *heap, size_t size);
void *HeapFree(Heap *heap, void *p);
