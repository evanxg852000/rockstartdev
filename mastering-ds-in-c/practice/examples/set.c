#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "set.h"


static void print_set(const Set* s) {
  ListItem *member;
  int *data, size, i;

  fprintf(stdout, "Set size is %d\n", size = set_size(s));
  
  i = 0;
  member = list_head(s);
  while(i < size) {
    data = list_data(member);
    fprintf(stdout, "set[%03d]=%03d\n", i, *data);
    member = list_next(member);
    i++;
  }
}

static int match_int(const void* a, const void* b) {
  return !memcmp(a, b, sizeof(int));
}

int main(int argc, char** argv) {
  Set set;
  int *data, retval, i;

  set_init(&set, match_int, free);
  fprintf(stdout, "Inserting 10 memebers\n");
  for(i = 9; i >= 0; i--) {
    if((data = (int *)malloc(sizeof(int))) == NULL)
      return 1;

    *data = i + 1;

    if((retval = set_insert(&set, data)) < 0)
      return 1;
    else if (retval == 1)
      free(data);
  }

  print_set(&set);
  fprintf(stdout, "Inserting the same members again\n");

  fprintf(stdout, "Destroying the sets\n");
  set_destroy(&set);

  return 0;
}
