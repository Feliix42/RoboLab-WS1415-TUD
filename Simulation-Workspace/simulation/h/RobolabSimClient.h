#include "./Configuration.h"
#include "./heap.h"

// DEFINITIONS

#define X_SIZE 13
#define Y_SIZE 13
#define MAX_DISTANCE 65000

// DATA STRUCTURES

struct node {
  int state;        // 0 for unvisited, 1 for visited, 2 for non-existing/unreachable
  char directions[4];   // which directions are available as destination?
  /* 0 - N    1 - O    2 - S    3 - W
   *
   * 0x00 (false) stands for "not available" , (true) for available */
  int distance;
  int visitedByDijkstra; // 0 = no    1 = yes
  int vorgaengerx, vorgaengery;
} node[X_SIZE][Y_SIZE];
