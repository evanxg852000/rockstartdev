#ifndef LIST_H
#define LIST_H

#include <stdbool.h>

typedef int (*matcher)(const void* a, const void* b);
typedef void (*deleter)(void* data);

typedef struct ListItem_ {
  void* data;
  struct ListItem_* next;
} ListItem;


typedef struct List_ {
  int size;
  matcher match;
  deleter destroy;

  ListItem *head;
  ListItem *tail;
} List;


void list_init(List *list, deleter destroy);

void list_destroy(List* list);

int list_ins_next(List* list, ListItem* element, const void* data);

int list_rem_next(List* list, ListItem* element, void** data);

#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, elem) ((elem) == (list)->head ? true : false)

#define list_is_tail(elem) ((elem)->next == NULL ? true : false)

#define list_data(elem) ((elem)->data)

#define list_next(elem) ((elem)->next)

#endif
