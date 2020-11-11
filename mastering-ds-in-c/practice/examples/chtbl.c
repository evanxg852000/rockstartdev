#include <stdio.h>

#include "chtbl.h"
#include "list.h"

#define TABLE_ZISE  11

static int match_char(const void* c, const void* d) {
  return (*(const char*)c == *(const char*)d);
}

static int h_char(const void *k){
  return *(const char*)k % TABLE_ZISE;
}


static void print_table(const CHTbl* htbl) {
  ListItem *elem;
  fprintf(stdout, "Table size is %d\n", chtbl_size(htbl));

  for(int i = 0; i < TABLE_ZISE; i++) {
    fprintf(stdout, "Bucket[%03d]=", i);
    for(elem = list_head(&htbl->table[i]); elem != NULL;
      elem = list_next(elem)) {
      fprintf(stdout, "%c", *(char*)list_data(elem));
    }
  }

  fprintf(stdout, "\n");
}


int main(int argc, char** argv) {
  CHTbl htbl;
  char *data, c;
  int retval, i;

  if(chtbl_init(&htbl, TABLE_ZISE, h_char, match_char, free) != 0)
    return 1;

  for(i = 0; i < TABLE_ZISE; i++) {
    if((data = (char*)malloc(sizeof(char))) == NULL)
      return 1;

    *data = ((5 + (i * 6)) % 23) + 'A';
    if(chtbl_insert(&htbl, data) != 0)
      return 1;

  }
  print_table(&htbl);

  chtbl_destroy(&htbl);
  return 0;
}
