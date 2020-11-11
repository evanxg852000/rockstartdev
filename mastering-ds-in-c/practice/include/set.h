#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include <stdbool.h>

#include "list.h"


typedef List Set;

void set_init(Set *set, matcher match, deleter destroy);

#define set_destroy list_destroy

int set_insert(Set* set, const void* data);

int set_remove(Set* set, void** data);

int set_union(Set* u, const Set* r, const Set* s);

int set_intersection(Set *i, const Set* r, const Set* s);

int set_difference(Set *d, const Set* r, const Set* s);

int set_is_member(const Set* set, const void *data);

int set_is_subset(const Set* r, const Set* s);

int set_is_equal(const Set* r, const Set* s);

#define set_size(set) ((set)->size)

#endif
