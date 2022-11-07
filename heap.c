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
void *HeapAlloc(Heap *heap, uint32_t size)
{
  if (size < MIN_ALLOC_SIZE) {
    size = MIN_ALLOC_SIZE;
  }
  uint32_t idx = GetListsIdx(size);
  Node *fitted = GetBestFit(heap->lists[idx], size);
  while (fitted == NULL) {
    if (++idx >= LIST_COUNT) {
      return NULL;
    }
    fitted = GetBestFit(heap->lists[idx], size);
  }

  if (fitted->size - size - OVERHEAD >= MIN_ALLOC_SIZE) {
    Node *remainder = (Node *)((void *)fitted + size + OVERHEAD);
    remainder->size = fitted->size - size - OVERHEAD;
    remainder->used = 0;
    remainder->next = NULL;
    remainder->prev = NULL;
    InitFooter(remainder);
    AddNode(heap->lists[GetListsIdx(remainder->size)], remainder);

    fitted->size = size;
    InitFooter(fitted);
  }

  fitted->used = 1;
  RemoveNode(heap->lists[idx], fitted);
  fitted->next = NULL;
  fitted->prev = NULL;
  return (void *)fitted + sizeof(Node);
}
void *HeapFree(Heap *heap, void *p)
{
  Node *newNode;

  uint8_t isFirst = 0;
  uint8_t isLast = 0;
  Node *toFree = (Node *)p - 1;
  Footer *footer = GetFooter(toFree);
  if ((void *)toFree == heap->start) {
    isFirst = 1;
  }
  if ((void *)(footer + 1) == heap->end) {
    isLast = 1;
  }

  if (!isFirst) {
    Node *prevNode = ((Footer *)toFree - 1)->header;
    if (!prevNode->used) {
      RemoveNode(heap->lists[GetListsIdx(prevNode->size)], prevNode);
      prevNode->size += toFree->size + OVERHEAD;
      InitFooter(prevNode);
      toFree = prevNode;
    }
  }
  if (!isLast) {
    Node *nextNode = (Node *)(footer + 1);
    if (!nextNode->used) {
      RemoveNode(heap->lists[GetListsIdx(nextNode->size)], nextNode);
      toFree->size += nextNode->size + OVERHEAD;
      InitFooter(toFree);
    }
  }

  toFree->used = 0;
  AddNode(heap->lists[GetListsIdx(toFree->size)], toFree);
}

void InitFooter(Node *node)
{
  Footer *footer = (Footer *)((void *)node + node->size + sizeof(Node));
  footer->header = node;
}

Footer *GetFooter(Node *node)
{
  return (Footer *)((void *)node + node->size + sizeof(Node));
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
