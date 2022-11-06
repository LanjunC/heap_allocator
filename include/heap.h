#ifndef _HEAP_H
#define _HEAP_H

#include "list.h"

#define HEAP_INIT_SIZE 0x10000
#define MIN_ALLOC_SIZE 4

typedef struct Heap {
  void *start;
  void *end;
  List *lists[LIST_COUNT];
} Heap;

typedef struct Footer {
  Node *header;
} Footer;

static size_t OVERHEAD = sizeof(Node) + sizeof(Footer);

void InitHeap(Heap *heap, void *p);
void *HeapMalloc(Heap *heap, size_t size);
void *HeapFree(Heap *heap, void *p);

void InitFooter(Node *node);
uint32_t GetListsIdx(size_t size);

#endif