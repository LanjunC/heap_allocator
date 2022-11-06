#ifndef _LIST_H
#define _LIST_H

#include <stdint.h>
#include <stddef.h>

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

void AddNode(List *list, Node *node);
void RemoveNode(List *list, Node *node);
Node *GetBestFit(List *list, size_t size);

#endif