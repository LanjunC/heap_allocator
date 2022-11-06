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
{}

Node *GetBestFit(List *list, size_t size)
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