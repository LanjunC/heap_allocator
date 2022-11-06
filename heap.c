#include "include/heap.h"
#include "include/list.h"

void InitHeap(Heap *heap, void *p)
{
  heap->start = p;

  Node *head = (Node *)p;
  head->used = 0;
  head->size = HEAP_INIT_SIZE - OVERHEAD;
  head->prev = NULL;
  head->next = NULL;

  InitFooter(head);

  AddNode(heap->lists[GetListsIdx(head->size)], head);

  heap->start = p;
  heap->end = p + HEAP_INIT_SIZE;
}
void *HeapMalloc(Heap *heap, uint32_t size)
{}
void *HeapFree(Heap *heap, void *p)
{}

void InitFooter(Node *node)
{
  Footer *footer = (void *)node + node->size + sizeof(node);
  footer->header = node;
}

uint32_t GetListsIdx(uint32_t size)
{
  uint32_t idx = 0;
  if (size < MIN_ALLOC_SIZE)
    size = MIN_ALLOC_SIZE;
  while (size >>= 1)
    idx++;
  idx -= 2;

  if (idx > LIST_COUNT - 1)
    idx = LIST_COUNT - 1;
  return idx;
}

void PrintLists(Heap *heap)
{
  printf("===Now print lists of heap:===\n");

  for (uint32_t i = 0; i < LIST_COUNT; i++) {
    printf("[%u]", i);
    PrintList(heap->lists[i]);
  }
  printf("==============================\n");
}
