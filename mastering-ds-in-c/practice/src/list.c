#include <stdlib.h>
#include <string.h>

#include "list.h"

void list_init(List* list, deleter destroy) {
  list->size = 0;
  list->destroy = destroy;
  list->head = list->tail = NULL;
}

void list_destroy(List* list) {
  void* data;

  while(list_size(list) > 0) {
    if(list_rem_next(list, NULL, (void**)&data) == 0 
      && list->destroy != NULL) {
      list->destroy(data);
    }
  }

  memset(list, 0, sizeof(List)); // clear structure
}

int list_ins_next(List* list, ListItem* elem, const void* data) {
  ListItem* new_elem;

  if((new_elem = (ListItem*)malloc(sizeof(ListItem))) == NULL)
    return -1;

  new_elem->data = (void*) data;

  if(elem == NULL) { //handle insert at head
    if(list_size(list) == 0)
      list->tail = new_elem;

    new_elem->next = list->head;
    list->head = new_elem;
  } else {
    if(elem->next == NULL)
      list->tail = new_elem;

    new_elem->next = elem->next;
    elem->next = new_elem;
  }

  list->size++;
  return 0;
}

int list_rem_next(List* list, ListItem* elem, void** data) {
  ListItem* old_elem;

  if(list_size(list) == 0)
    return -1;

  if(elem == NULL) { //handle rem from head 
    *data = list->head->data;
    old_elem = list->head;
    list->head = list->head->next;
    
    if(list_size(list) == 1)
      list->tail = NULL;
  } else {
    if(elem->next == NULL)
      return -1;

    *data = elem->next->data;
    old_elem = elem->next;
    elem->next = elem->next->next;

    if(elem->next == NULL)
      list->tail = elem;
  }

  free(old_elem);
  list->size--;
  return 0;
}
