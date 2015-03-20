typedef struct heap* hpointer;
struct heap {
  int x;
  int y;
  hpointer prev;
  hpointer next;
} heap;


hpointer heap_push (int a, int b, hpointer h);
int heap_pop(int *a, int *b);
