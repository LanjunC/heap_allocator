#ifndef _HEAP_H
#define _HEAP_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>

#define HEAP_INIT_SIZE 0x10000
#define MIN_ALLOC_SIZE 4

#define LIST_COUNT 9

typedef struct Node {
  /* Memory alignment. Prevent compiler optimization disturbing address computation. */
  uint32_t used;
  uint32_t size;
  struct Node *prev;
  struct Node *next;
} Node;

typedef struct List {
  Node *head;
} List;

typedef struct Heap {
  void *start;
  void *end;
  List *lists[LIST_COUNT];
} Heap;

typedef struct Footer {
  Node *header;
} Footer;

static uint32_t OVERHEAD = sizeof(Node) + sizeof(Footer);

void InitHeap(Heap *heap, void *p);
void *HeapAlloc(Heap *heap, uint32_t size);
void *HeapFree(Heap *heap, void *p);

void InitFooter(Node *node);
Footer *GetFooter(Node *node);
uint32_t GetListsIdx(uint32_t size);
void PrintLists(Heap *heap);

#endif