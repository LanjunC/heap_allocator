#include "include/list.h"
#include <assert.h>

void AddNode(List *list, Node *node)
{
  assert(list != NULL);
  if (list->head == NULL) {
    list->head = node;
    node->prev = NULL;
    node->next = NULL;
    return;
  }

  Node *tmp = list->head;
  Node *previous = NULL;
  while (tmp != NULL && tmp->size < node->size) {
    previous = tmp;
    tmp = tmp->next;
  }

  if (tmp == NULL) {
    previous->next = node;
    node->prev = previous;
    node->next = NULL;
    return;
  } else {
    node->next = tmp;
    node->prev = previous;
    if (previous == NULL) {
      tmp->prev = node;
      list->head = node;
    } else {
      // at middle of list
      previous->next = node;
      tmp->prev = node;
    }
    return;
  }
}
void RemoveNode(List *list, Node *node)
{
  assert(list->head != NULL);
  assert(node != NULL);
  if (list->head == node) {
    list->head = node->next;
    node->next = NULL;
    node->prev = NULL;
    return;
  }

  {
    // Just check correctness. Remove this latter.
    Node *cur = list->head->next;
    while (cur != NULL && cur != node) {
      cur = cur->next;
    }
    assert(cur != NULL);
  }

  if (node->next == NULL) {
    node->prev->next = node->next;
  } else {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
  node->next = NULL;
  node->prev = NULL;
  return;
}

Node *GetBestFit(List *list, uint32_t size)
{
  assert(list != NULL);
  if (list->head == NULL) {
    return NULL;
  }

  Node *node = list->head;
  while (node != NULL) {
    if (node->size >= size) {
      return node;
    }
    node = node->next;
  }
  return NULL;
}

void PrintList(List *list)
{
  printf("In this list: ");
  Node *node = list->head;
  while (node != NULL) {
    printf("[ptr:%lu][size:%u][totSize:%u][used:%u]", (uint64_t)node, node->size, node->size + OVERHEAD, node->used);
    node = node->next;
  }
  printf("\n");
}