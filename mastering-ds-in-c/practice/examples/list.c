#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"


static void print_list(const List* list) {
  ListItem* elem;
  int* data, i;

  fprintf(stdout, "List size is %d\n", list_size(list));
  
  i = 0;
  elem = list_head(list);

  while(true) {
    data = list_data(elem);
    fprintf(stdout, "list[%03d]=%03d\n", i, *data);

    if(list_is_tail(elem))
      break;
    
    i++;
    elem = list_next(elem);
  }

}

int main(int argc, char** argv) {
  List list;
  ListItem *elem;
  int *data, i;

  list_init(&list, free);

  elem = list_head(&list);
  for(i = 10; i > 0; i--) {
    if((data = (int*)malloc(sizeof(int))) == NULL)
      return 1;

    *data = i;
    if(list_ins_next(&list, NULL, data) != 0)
      return 1;
  }

  print_list(&list);
}
