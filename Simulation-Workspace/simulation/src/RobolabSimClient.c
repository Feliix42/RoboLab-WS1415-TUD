#include "../h/RobolabSimClient.h"

int direction = 0;
    /* aktuelle Blickrichtung des Roboters (am Beginn N)
     * 0 = N; 1 = O; 2 = S; 3 = W
     *
     * IDEE: Wenn der Roboter an die Kreuzung kommt:
     * Biegt er RECHTS ab, erhöhe direction um 1 (mod 4).
     * Biegt er LINKS ab, vermindere direction um 1 (mod 4). */

int token = 3;
hpointer knownNodes = NULL;
int nodeCount = 0;


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



void checkIntersection(int x, int y) {
  if (node[x][y].state == 1)
    return;

  int intersection = Robot_GetIntersections();

  if(intersection & NORTH) {
    node[x][y].directions[0] = 0x01;
    node[x][y+1].directions[2] = 1;
    if(node[x][y+1].state == 2)
    {
      node[x][y+1].state = 0;
      heap_push(x,y+1,&knownNodes);
      nodeCount++;
    }
  }


  if(intersection & EAST) {
    node[x][y].directions[1] = 0x01;
    node[x+1][y].directions[3] = 1;
    if(node[x+1][y].state == 2)
    {
      node[x+1][y].state = 0;
      heap_push(x+1,y,&knownNodes);
      nodeCount++;
    }
  }

  if(intersection & SOUTH) {
    node[x][y].directions[2] = 0x01;
    node[x][y-1].directions[0] = 1;
    if(node[x][y-1].state == 2)
    {
      node[x][y-1].state = 0;
      heap_push(x,y-1,&knownNodes);
      nodeCount++;
    }
  }


  if(intersection & WEST) {
    node[x][y].directions[3] = 0x01;
    node[x-x][y].directions[1] = 1;
    if(node[x-1][y].state == 2)
    {
      node[x-1][y].state = 0;
      heap_push(x-1,y,&knownNodes);
      nodeCount++;
    }
  }
}


int checkNodeAvailable(int x, int y, int dir) {
  switch(dir) {
    case 0:
      y++;
      break;
    case 1:
      x++;
      break;
    case 2:
      y--;
      break;
    case 3:
      x--;
      break;
  }

  if(node[x][y].state == 0)
    return 1;
  else
    return 0;
}

// find a way from startx/y to targetx/y. If nextSteps is NULL, the robot will instantly follow this way. If not, the waypoints will be added to nextSteps.
void go(int startx, int starty, int targetx, int targety, int simudx, int simudy,hpointer *nextSteps)
{
  int goThisWay = 0; // check nextSteps
  if (nextSteps == NULL)
  {
    goThisWay=1; // we want to go this way
    hpointer temphp = NULL;
    nextSteps = &temphp; // temporary list
  }

  resetDistance(); // Initialisation for dijkstra
  node[startx][starty].distance=0; // starting point

  int nodesRemaining = nodeCount;


  while(nodesRemaining>0) // there are more nodes out there
  {
      int mindistance=MAX_DISTANCE; // searching the node with shortest distance
      int minx,miny;

      hpointer temp=knownNodes;
      while(temp != NULL) // go through the list
      {
        if (node[temp->x][temp->y].visitedByDijkstra==0) // not visited yet
        {
            if (node[temp->x][temp->y].distance < mindistance) // distance is smaller than the minimunm
            {
              mindistance = node[temp->x][temp->y].distance; // it's the new minimum then!
              minx=temp->x;
              miny=temp->y;
            }
        }
        temp=temp->next; // next list entry
      }

      int d;
      for(d=0;d<4;d++) // propagate the distance to all neighbours
      {
        if (node[minx][miny].directions[d]) // is there an edge?
        {
            int mydistance=node[minx][miny].distance; // distance of our current node
            int dx,dy;
            dirToXY(d,&dx,&dy);

            if (mydistance+1<node[minx+dx][miny+dy].distance) // it's better to go over our node to reach the other node
            {
                node[minx+dx][miny+dy].distance=mydistance+1; // set a new distance for the other node
                node[minx+dx][miny+dy].vorgaengerx=minx; // and our node as the predecessor (that means "vorgaenger", according to PONS)
                node[minx+dx][miny+dy].vorgaengery=miny;
            }
        }
      }

      node[minx][miny].visitedByDijkstra=1; // we just visited this node
      nodesRemaining--; // one less out there

      if (minx==targetx && miny==targety) // is this already the target node?
        break; // dijkstra found the nearest way to it.

  } // we set all the distances and predecessors we need


  // create way
  int tx=targetx,ty=targety,ntx;
  while (tx!=startx||ty!=starty)
  {
    heap_push(tx,ty,nextSteps); // some predecessor jumping and saving the way
    ntx=node[tx][ty].vorgaengerx;
    ty=node[tx][ty].vorgaengery;
    tx=ntx;
  }

  if (goThisWay) // do we want to go this way NOW?
  {
     hpointer temp = *nextSteps;
     while (temp!=NULL)
     {
        Robot_Move(temp->x+simudx,temp->y+simudy); // move move move
        temp=temp->next;
     }
  }
}


// return 1 if found one, 0 if there are no more
int findBacktrackNode(int *ox, int *oy, hpointer *heap)
{
    int x,y;
    while (heap_pop(&x,&y,heap)) // go through the nodes
    {
        int waysremaining = 0;

        int i;
        for(i = 0; i <= 3; i++) {
          if((node[x][y].directions[i])) // check for all directions...
          {
            if(checkNodeAvailable(x, y, i)) // if there is an unvisited node
            {
              waysremaining = 1; // there is
              break;
            }
          }
        }

        if (waysremaining) // there is a unvisited node near this node
        {
            *ox = x; //return that node
            *oy = y;
            return 1;
        }
    }

    return 0; // there was nothing.
}

// go back to start from current position x/y. instantly, if nextStep is NULL, added to nextSteps if is a pointer.
void backToStart(int x, int y, int dx, int dy, hpointer *nextSteps) {
  go(x,y,6,6,dx,dy,nextSteps); // 6/6 is start
  return;
}

int main(void) {
  int x = 6, y = 6, driveTo, running = 1;

  int dx = -6, dy = -6;

  initArray();

  heap_push(x,y,&knownNodes);
  nodeCount++;


  hpointer heap = NULL;
  hpointer nextSteps = NULL;

  Robot_Move(0,0);

  while(running) {
    printf("%d %d\n", x+dx, y+dy);

    checkIntersection(x, y);

    node[x][y].state = 1;

    if (!heap_pop(&x,&y,&nextSteps)) // no given way? x/y is the next step otherwise
    {
        driveTo = 4;
        int i;
        for(i = 0; i <= 3; i++) {
          if((node[x][y].directions[i]))
            if(checkNodeAvailable(x, y, i))
              driveTo = i;
        }

        int bx,by;

        switch(driveTo) {
          case 0:
            printf("Go NORTH\n");
            heap_push(x,y,&heap);
            y++;
            break;
          case 1:
            printf("Go EAST\n");
            heap_push(x,y,&heap);
            x++;
            break;
          case 2:
            printf("Go SOUTH\n");
            heap_push(x,y,&heap);
            y--;
            break;
          case 3:
            printf("Go WEST\n");
            heap_push(x,y,&heap);
            x--;
            break;
          case 4:
            if (findBacktrackNode(&bx,&by,&heap))
            {
                printf("going back to %d %d\n",bx,by);
                go(x,y,bx,by,dx,dy,&nextSteps);
                heap_pop(&x,&y,&nextSteps);
            }
            else
            {
                printf("Labyrinth vollständig erkundet.\nEnde.\n");
                running = 0;
            }
            break;
        }
    }


    if (running)
    {
        int found = Robot_Move(x+dx,y+dy);
        if(found == ROBOT_TOKENFOUND)
          token--;
        if(!token) {
          printf("found every token!\n");
          backToStart(x, y, dx, dy, NULL);
          running = 0;
        }
    }
  }
	return EXIT_SUCCESS;
}
