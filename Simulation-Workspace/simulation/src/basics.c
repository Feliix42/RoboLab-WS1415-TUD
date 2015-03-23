#include "../h/basics.h"


// Reset nodes for dijkstra
void resetDistance(void) {
  int i, j;
  for(i = 0; i < X_SIZE; i++) {
    for(j = 0; j < Y_SIZE; j++) {
      node[i][j].distance = MAX_DISTANCE;
      node[i][j].visitedByDijkstra = 0;
    }
  }
}


//Init nodes
void initArray(void) {
  int i, j, d;
  for(i = 0; i < X_SIZE; i++) {
    for(j = 0; j < Y_SIZE; j++) {
      node[i][j].state = 2;
      for (d=0;d<4;d++) node[i][j].directions[d]=0;
    }
  }
  resetDistance();
}


//get dx/dy from direction
void dirToXY(int direction, int *dx, int *dy)
{
    *dx=0;
    *dy=0;
    switch(direction) {
    case 0:
      *dy=*dy+1;
      break;
    case 1:
      *dx=*dx+1;
      break;
    case 2:
      *dy=*dy-1;
      break;
    case 3:
      *dx=*dx-1;
      break;
  }
  return;
}



void checkIntersection(int x, int y, hpointer *knownNodes, int *nodeCount) {
  if (node[x][y].state == 1)
    return;

  int intersection = Robot_GetIntersections();

  if(intersection & NORTH) {
    node[x][y].directions[0] = 0x01;
    node[x][y+1].directions[2] = 1;
    if(node[x][y+1].state == 2)
    {
      node[x][y+1].state = 0;
      heap_push(x,y+1,knownNodes);
      (*nodeCount)++;
    }
  }


  if(intersection & EAST) {
    node[x][y].directions[1] = 0x01;
    node[x+1][y].directions[3] = 1;
    if(node[x+1][y].state == 2)
    {
      node[x+1][y].state = 0;
      heap_push(x+1,y,knownNodes);
      (*nodeCount)++;
    }
  }

  if(intersection & SOUTH) {
    node[x][y].directions[2] = 0x01;
    node[x][y-1].directions[0] = 1;
    if(node[x][y-1].state == 2)
    {
      node[x][y-1].state = 0;
      heap_push(x,y-1,knownNodes);
      (*nodeCount)++;
    }
  }


  if(intersection & WEST) {
    node[x][y].directions[3] = 0x01;
    node[x-x][y].directions[1] = 1;
    if(node[x-1][y].state == 2)
    {
      node[x-1][y].state = 0;
      heap_push(x-1,y,knownNodes);
      (*nodeCount)++;
    }
  }
}


int checkNodeAvailable(int x, int y, int dir) {
  int dx=0,dy=0;
  dirToXY(dir, &dx, &dy);
  x+=dx;
  y+=dy;
  if(node[x][y].state == 0)
    return 1;
  else
    return 0;
}

int lastx=6, lasty=6;

int robot_move(int x, int y)
{
    int dx=x-lastx;
    int dy=y-lasty;
    
    lastx=x;
    lasty=y;
    
    int direction = 0;
    
    if (dx==1)
    {
        if (dy==1) direction=0;
        else direction=0;
    }
    else
    {
        if (dy==1) direction=0;
        else direction=0;
    }
     

    //return move(direction);
    return Robot_Move(x,y);
}

