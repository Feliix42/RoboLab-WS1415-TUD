#ifndef HEAP_H_
#define HEAP_H_

// INCLUDES

#include <stdlib.h>

// DATA STRUCTURES

typedef struct heap* hpointer;
struct heap {
  int x;
  int y;
  hpointer next;
} heap;

// FUNCTIONS

void heap_push (int x, int y, hpointer* h);
int heap_pop(int *x, int *y, hpointer* h);

#endif // HEAP_H_
