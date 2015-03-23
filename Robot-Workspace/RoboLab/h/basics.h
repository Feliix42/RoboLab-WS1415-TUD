#include "heap.h"

// DEFINITIONS

#define X_SIZE 13
#define Y_SIZE 13
#define MAX_DISTANCE 65000

#define NORTH 0x10
#define SOUTH 0x20
#define WEST 0x40
#define EAST 0x80

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

//FUNCTIONS

void resetdistance(void);
void initArray(void);
void dirToXY(int direction, int *dx, int *dy);
void checkIntersection(int x, int y, hpointer *knownNodes, int *nodeCount);
int checkNodeAvailable(int x, int y, int dir);
int robot_move(int x, int y);
