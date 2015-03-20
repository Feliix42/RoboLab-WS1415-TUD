#include "../h/heap.h"

void heap_push (int x, int y, hpointer* h) {
  hpointer q = (hpointer) malloc(sizeof(heap));
  q->x = x;
  q->y = y;
  q->next = *h;
  h = &q;
  return;
}


int heap_pop(int *x, int *y, hpointer* h) {
  if(*h == NULL)
    return 0;

  *x = (*h)->x;
  *y = (*h)->y;

  hpointer q = *h;
  *h = q->next;
  free(q);
  return 1;
}
