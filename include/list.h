#ifndef _LIST_H
#define _LIST_H

#include "heap.h"

void AddNode(List *list, Node *node);
void RemoveNode(List *list, Node *node);

Node *GetBestFit(List *list, uint32_t size);
void PrintList(List *list);

#endif