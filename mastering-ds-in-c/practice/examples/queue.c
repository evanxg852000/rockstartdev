#include <stdlib.h>
#include <stdio.h>

#include "list.h"
#include "queue.h"


static void print_queue(const Queue *queue) {
  ListItem *elem;
  int *data, size, i;

  fprintf(stdout, "Queue size is %d\n", size = queue_size(queue));
  
  i = 0;
  elem = list_head(queue);
  while(i < size) {
    data = list_data(elem);
    fprintf(stdout, "queue[%03d]=%03d\n", i, *data);
    elem = list_next(elem);
    i++;
  }
}


int main(int argc, char **argv) {
  Queue queue;
  int *data, i;

  queue_init(&queue, free);
  fprintf(stdout, "Enqueuing 10 elements\n");
  for(i = 0; i < 10; i++) {
    if((data = (int *)malloc(sizeof(int))) == NULL)
      return 1;

    *data = i + 1;
    if(queue_enqueue(&queue, data) != 0)
      return 1;
  }

  print_queue(&queue);

  fprintf(stdout, "Dequeuing 5 elements\n");
  for(i =0 ; i < 5; i++) {
    if(queue_dequeue(&queue, (void **)&data) == 0)
      free(data);
    else
      return 1;
  }

  print_queue(&queue);

  fprintf(stdout, "Destroying the queue\n");
  queue_destroy(&queue);
  
  return 0;
}
