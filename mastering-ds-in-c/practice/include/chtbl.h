#ifndef CHTABL_H
#define CHTABL_H

#include <stdlib.h>
#include "list.h"

typedef int (*hasher)(const void *key);

typedef struct CHTbl_ {
  int buckets;
  hasher hash;
  matcher match;
  deleter destroy;
  int size;
  List *table;
} CHTbl;


int chtbl_init(CHTbl *htbl, int buckets, 
  hasher hash, matcher match, deleter destroy);

void chtbl_destroy(CHTbl *htbl);

int chtbl_insert(CHTbl *htbl, const void* data);

int chtbl_remove(CHTbl *htbl, void** data);

int chtbl_lookup(const CHTbl* htbl, void **data);

#define chtbl_size(htbl) ((htbl)->size)

#endif
