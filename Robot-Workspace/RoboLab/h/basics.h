#ifndef BASICS_H_
#define BASICS_H_

#include "heap.h"
#include "main.h"

// DEFINITIONS

#define X_SIZE 13
#define Y_SIZE 13
#define MAX_DISTANCE 65000

#define NORTH 0x10
#define SOUTH 0x20
#define WEST 0x40
#define EAST 0x80

#define ROBOT_FAIL        0x00
#define ROBOT_SUCCESS     0x01
#define ROBOT_TOKENFOUND  0x02

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

void resetDistance(void);
void initArray(void);
void dirToXY(int direction, int *dx, int *dy);
int checkIntersection(int x, int y, hpointer *knownNodes, int *nodeCount);
int checkNodeAvailable(int x, int y, int dir);
int Robot_Move(int x, int y);

#endif // BASICS_H_
