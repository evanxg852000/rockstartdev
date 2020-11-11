#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "chtbl.h"


int chtbl_init(CHTbl* htbl, int buckets, 
  hasher hash, matcher match, deleter destroy) {
  if((htbl->table = (List*)malloc(buckets * sizeof(List))) == NULL)
    return -1;

  htbl->buckets = buckets;
  for(int i = 0; i < htbl->buckets; i++)
    list_init(&htbl->table[i], destroy);

  htbl->hash = hash;
  htbl->match = match;
  htbl->destroy = destroy;

  htbl->size = 0;
  return 0;
}

void chtbl_destroy(CHTbl* htbl) {
  for(int i = 0; i < htbl->buckets; i++) {
    list_destroy(&htbl->table[i]);
  }

  free(htbl->table);
  memset(htbl, 0, sizeof(CHTbl));
}

int chtbl_insert(CHTbl *htbl, const void *data) {
  void *temp;
  int bucket, retval;

  temp = (void *)data;
  if(chtbl_lookup(htbl, &temp) == 0)
    return 1;

  bucket = htbl->hash(data) % htbl->buckets;
  if((retval = list_ins_next(&htbl->table[bucket], NULL, data)) == 0)
    htbl->size++;

  return retval;
}

int chtbl_remove(CHTbl* htbl, void** data) {
  ListItem *elem, *prev;
  int bucket;

  bucket = htbl->hash(*data) % htbl->buckets;
  prev = NULL;

  for(elem = list_head(&htbl->table[bucket]); elem != NULL; elem = list_next(elem)) {
    if(htbl->match(*data, list_data(elem))) {
      if(list_rem_next(&htbl->table[bucket], prev, data) == 0) {
        htbl->size--;
        return 0;
      } else {
        return -1;
      }
    }

    prev = elem;
  }

  return -1;
}

int chtbl_lookup(const CHTbl* htbl, void** data) {
  ListItem* elem;
  int bucket;

  bucket = htbl->hash(*data) % htbl->buckets;
  for(elem = list_head(&htbl->table[bucket]); elem != NULL; elem = list_next(elem)) {
    if(htbl->match(*data, list_data(elem))) {
      *data = list_data(elem);
      return 0;
    }
  }

  return false;
}
