#include <stdio.h>

#include "ohtbl.h"

#define TABLE_ZISE 11

static int match_char(const void* c1, const void* c2) {
  return (*(const char*)c1 == *(const char*)c2);
}

static int h1_char(const void* k) {
  return *(const char*)k % TABLE_ZISE;
}

static int h2_char(const void* k) {
  return 1 + *(const char*)k % (TABLE_ZISE -2);
}


static void print_table(const OHTbl* htbl) {
  int i;

  fprintf(stdout, "Table size is %d\n", ohtbl_size(htbl));
  for(i = 0; i < TABLE_ZISE; i++) {
    if(htbl->table[i] != NULL && htbl->table[i] != htbl->vacated) {
      fprintf(stdout, "Slot[%03d]=%c\n", i , *(char*)htbl->table[i]);
    } else {
      fprintf(stdout, "Slot[%03d]= \n", i);
    }
  }
}

int main(int argc, char** argv) {
  OHTbl htbl;
  char *data, c;
  int retval, i, j;

  if(ohtbl_init(&htbl, TABLE_ZISE, h1_char, h2_char, match_char, free) != 0)
    return 1;

  for(i = 0; i < 5; i++) {
    if((data = (char*)malloc(sizeof(char))) == NULL)
      return 1;

    *data = ((8 + (i * 9)) % 23) + 'A';
    fprintf(stdout, "Hashing %c:", *data);

    for (j = 0; j < TABLE_ZISE; j++)
     fprintf(stdout," %02d", (h1_char(data) + (j * h2_char(data))) % TABLE_ZISE);

    fprintf(stdout, "\n");

    if (ohtbl_insert(&htbl, data) != 0)
      return 1;

     print_table(&htbl);
  }

  ohtbl_destroy(&htbl);
}
