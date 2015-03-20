typedef struct heap* hpointer;
struct heap {
  int x;
  int y;
  hpointer prev;
  hpointer next;
} heap;


void heap_push (int a, int b);
int heap_pop(int *a, int *b);
