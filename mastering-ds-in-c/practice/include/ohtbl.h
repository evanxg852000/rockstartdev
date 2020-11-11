#ifndef OHTBL_H
#define OHTBL_H

#include <stdlib.h>

typedef int (*hasher)(const void *k);
typedef int (*matcher)(const void* k1, const void* k2);
typedef void (*deleter)(void* data);

typedef struct OHTbl_ {
  int positions;
  void *vacated;

  hasher hash1;
  hasher hash2;
  matcher match;
  deleter destroy;

  int size;
  void **table;
} OHTbl;


int ohtbl_init(OHTbl* htbl, int positions, hasher h1, hasher h2,
  matcher match, deleter destroy);

void ohtbl_destroy(OHTbl* htbl);

int ohtbl_insert(OHTbl* htbl, const void* data);

int ohtbl_remove(OHTbl* htbl, void** data);

int ohtbl_lookup(const OHTbl* htbl, void** data);

#define ohtbl_size(htbl)  ((htbl)->size)

#endif
