#include "include/heap.h"
#include <string.h>
#include <stdlib.h>

// TODO: test with google test
int main(int argc, char **argv)
{
  Heap *heap = (Heap *)malloc(sizeof(Heap));
  memset(heap, 0, sizeof(heap));

  void *initedChunk = malloc(HEAP_INIT_SIZE);
  memset(initedChunk, 0, HEAP_INIT_SIZE);

  for (int i = 0; i < LIST_COUNT; i++) {
    heap->lists[i] = malloc(sizeof(List));
    memset(heap->lists[i], 0, sizeof(List));
  }

  InitHeap(heap, initedChunk);
  printf("inited chunk=ptr[%lu]\n", (uint64_t)initedChunk);
  printf("heap->start=%lu, end=%lu\n", (uint64_t)heap->start, (uint64_t)heap->end);
  PrintLists(heap);

  uint32_t toAllocated[] = {2, 4, 8, 10, 1024, HEAP_INIT_SIZE};
  uint32_t count = sizeof(toAllocated) / sizeof(uint32_t);
  void *toFree[count];
  memset(toFree, 0, sizeof(toFree));
  for (uint32_t i = 0; i < count; i++) {
    void *p = HeapAlloc(heap, toAllocated[i]);
    if (p != NULL) {
      printf("heap alloc success. target size=%u, actual=%u, ptr=%lu\n",
          toAllocated[i],
          ((Node *)p - 1)->size,
          (uint64_t)p);
      toFree[i] = p;
    } else {
      printf("heap alloc fail. target size=%u\n", toAllocated[i]);
    }
  }

  for (uint32_t i = 0; i < count / 2; i++) {
    if (toFree[i] != NULL) {
      printf("start heap free...\n");
      HeapFree(heap, toFree[i]);
      PrintLists(heap);
      printf("heap free success.\n");
    } else {
      printf("nothing to free...\n");
    }
  }
  for (uint32_t i = count - 1; i >= count / 2; i--) {
    if (toFree[i] != NULL) {
      printf("start heap free...\n");
      HeapFree(heap, toFree[i]);
      PrintLists(heap);
      printf("heap free success.\n");
    } else {
      printf("nothing to free...\n");
    }
  }
}