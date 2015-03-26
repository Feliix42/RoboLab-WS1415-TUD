#include "../h/algorithms.h"

int token = 3;
hpointer knownNodes = NULL;
int nodeCount = 0;

// find a way from startx/y to targetx/y. If nextSteps is NULL, the robot will instantly follow this way. If not, the waypoints will be added to nextSteps.
void dijkstra(int startx, int starty, int targetx, int targety, int simudx, int simudy,hpointer *nextSteps)
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
      int minx=0,miny=0;

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
  dijkstra(x,y,6,6,dx,dy,nextSteps); // 6/6 is start
  return;
}

void brain(void) {
  token = 3;
  knownNodes = NULL;
  nodeCount = 0;


  int x = 6, y = 6, driveTo, running = 1;

  int dx = 0, dy = 0;

  initArray();

  heap_push(x,y,&knownNodes);
  nodeCount++;


  hpointer heap = NULL;
  hpointer nextSteps = NULL;

  int found = robot_move(0);
  if(found == ROBOT_TOKENFOUND)
    token--;

  while(running) {
    checkIntersection(x, y, &knownNodes, &nodeCount);

    node[x][y].state = 1;

    if (!heap_pop(&x,&y,&nextSteps)) // no given way? x/y is the next step otherwise
    {
        driveTo = 4;
        int i;
        for(i = 0; i <= 3; i++) {
          if (i != 2) // SOUTH shall be last, because of starting-edge reasons.
            if(node[x][y].directions[i])
              if(checkNodeAvailable(x, y, i))
              {
                driveTo = i;
                break;
              }
        }
        if (driveTo == 4) // Didn't found one yet
          if (node[x][y].directions[2]) // SOUTH, you can do it!
            if(checkNodeAvailable(x, y, 2))
              driveTo = 2;

        int bx,by;

        switch(driveTo) {
          case 0:
            heap_push(x,y,&heap);
            y++;
            break;
          case 1:
            heap_push(x,y,&heap);
            x++;
            break;
          case 2:
            heap_push(x,y,&heap);
            y--;
            break;
          case 3:
            heap_push(x,y,&heap);
            x--;
            break;
          case 4:
            if (findBacktrackNode(&bx,&by,&heap))
            {
                dijkstra(x,y,bx,by,dx,dy,&nextSteps);
                heap_pop(&x,&y,&nextSteps);
            }
            else
            {
                display_clear(1);
                display_goto_xy(0,3);
                display_string("Discovered EVERYTHING.");
                display_update();
                finish(VOLUME);
                running = 0;
            }
            break;
        }
    }


    if (running)
    {
        found = Robot_Move(x+dx,y+dy);
        if(found == ROBOT_TOKENFOUND)
          token--;
        if(!token) {
          display_clear(1);
          display_goto_xy(0,3);
          display_string("Found all Tokens!");
          display_update();
          checkIntersection(x, y, &knownNodes, &nodeCount);
          backToStart(x, y, dx, dy, NULL);
          finish(VOLUME);
          running = 0;
        }
    }
  }
	return;
}
