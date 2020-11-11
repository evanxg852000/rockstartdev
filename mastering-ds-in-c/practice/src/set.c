#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "set.h"


void set_init(Set* set, matcher match, deleter destroy) {
  list_init(set, destroy);
  set->match = match;
}

int set_insert(Set *set, const void* data) {
  if(set_is_member(set, data))
    return 1;

  return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set* set, void** data) {
  ListItem *member, *prev;

  prev = NULL;
  for(member = list_head(set); member != NULL; member = list_next(member)) {
    if(set->match(*data, list_data(member)))
      break;

    prev = member;
  }

  if(member == NULL)
    return -1;

  return list_rem_next(set, prev, data);
}

int set_union(Set* u, const Set* r, const Set* s) {
  ListItem* member;
  void* data;

  set_init(u, s->match, NULL);

  //insert memebers of set1
  for(member = list_head(r); member != NULL; member = list_next(member)) {
    data = list_data(member);
    if(list_ins_next(u, list_tail(u), data) != 0) {
      set_destroy(u);
      return -1;
    }
  }

  //insert members of set 2
  for(member = list_head(s); member != NULL; member = list_next(member)) {
    if(set_is_member(u, list_data(member))){
      continue;
    } else {
      data = list_data(member);
      if(list_ins_next(u, list_tail(u), data) != 0) {
        set_destroy(u);
        return -1;
      }   
    }
  }
  return 0;
}

int set_intersection(Set *i, const Set* r, const Set* s) {
  ListItem *member;
  void* data;

  set_init(i, r->match, NULL);

  for(member = list_head(r); member != NULL; member = list_next(member)) {
    if(set_is_member(s, list_data(member))){
      data = list_data(member);
      if(list_ins_next(i, list_tail(i), data) != 0) {
        set_destroy(i);
        return -1;
      }
    }
  }
  return 0;
}


int set_difference(Set* d, const Set* r, const Set* s) {
  ListItem* member;
  void* data;

  set_init(d, r->match, NULL);

  for(member = list_head(r); member != NULL; member = list_next(member)) {
    if(!set_is_member(s, list_data(member))) {
      data = list_data(member);
      if(list_ins_next(d, list_tail(d), data) != 0){
        set_destroy(d);
        return -1;
      }
    }
  }
  return 0; 
}

int set_is_member(const Set* s, const void* data) {
  ListItem* member;
  for(member = list_head(s); member != NULL; member = list_next(member)) {
    if(s->match(data, list_data(member)))
      return 1;
  }
  return 0;
}

int set_is_subset(const Set* r, const Set* s) {
  ListItem* member;
  if(set_size(r) > set_size(s))
    return 0;

  for(member = list_head(r); member != NULL; member = list_next(member)) {
    if(!set_is_member(s, list_data(member))){
      return 0;
    }
  }

  return 1;
}

int set_is_equal(const Set* r, const Set* s) {
  if(set_size(r) != set_size(s))
    return 0;

  return set_is_subset(r, s);
}
