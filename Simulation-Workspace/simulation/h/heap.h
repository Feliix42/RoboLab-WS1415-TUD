#include <stdlib.h>

//GEHOERT HIER NICHT HIN!!!11!!
#define MAX_DISTANCE 65000

typedef struct heap* hpointer;
struct heap {
  int x;
  int y;
  hpointer next;
} heap;


void heap_push (int x, int y, hpointer* h);
int heap_pop(int *x, int *y, hpointer* h);
