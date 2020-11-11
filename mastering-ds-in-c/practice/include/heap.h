#ifndef HEAP_H
#define HEAP_H

typedef int (*comparer)(const void *k1, const void *k2);
typedef void (*deleter)(void *data);

typedef struct Heap_ {
  int size;
  comparer compare;
  deleter destroy;

  void **tree;
} Heap;

void heap_init(Heap *heap, comparer compare, deleter destroy);

void heap_destroy(Heap *heap);

int heap_insert(Heap *heap, const void *data);

int heap_extract(Heap *heap, void **data);

#define heap_size(heap) ((heap)->size)

#endif
