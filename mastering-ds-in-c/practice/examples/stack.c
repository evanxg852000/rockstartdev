#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "stack.h"


static void print_stack(const Stack *stack) {
  ListItem *elem;
  int *data, size, i;

  fprintf(stdout, "Stack size is %d\n", size = stack_size(stack));

  i = 0;
  elem = list_head(stack);

  while(i < size) {
    data = list_data(elem);
    fprintf(stdout, "stack[%03d]=%03d\n", i, *data);
    elem = list_next(elem);
    i++;
  }
}


int main(int argc, char **argv) {
  Stack stack;
  int *data, i;

  stack_init(&stack, free);
  fprintf(stdout, "Pushing 10 elements\n");
  for(i = 0; i < 10; i++) {
    if((data = (int*)malloc(sizeof(int))) == NULL)
      return 1;

    *data = i + 1;
    if(stack_push(&stack, data) != 0)
      return 1;
  }

  print_stack(&stack);

  fprintf(stdout, "Popping 5 elements\n");
  for(i = 0; i < 5; i++) {
    if(stack_pop(&stack, (void**)&data) == 0)
      free(data);
    else
      return 1;
  }

  print_stack(&stack);

  fprintf(stdout, "Destroying the stack\n");
  stack_destroy(&stack);
  return 0;
}
