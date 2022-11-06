#include "include/heap.h"
#include <string.h>
#include <stdlib.h>
#include "gtest/gtest.h"

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
}