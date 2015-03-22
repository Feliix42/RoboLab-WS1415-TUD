#include "../h/Configuration.h"
#include "../h/heap.h"


#define X_SIZE 13
#define Y_SIZE 13

int direction = 0;
    /* aktuelle Blickrichtung des Roboters (am Beginn N)
     * 0 = N; 1 = O; 2 = S; 3 = W
     *
     * IDEE: Wenn der Roboter an die Kreuzung kommt:
     * Biegt er RECHTS ab, erhöhe direction um 1 (mod 4).
     * Biegt er LINKS ab, vermindere direction um 1 (mod 4). */

struct node {
  int state;        // 0 for unvisited, 1 for visited, 2 for non-existing/unreachable
  char directions[4];   // in welche Richtungen kann man fahren?
  /* 0 - N    1 - O    2 - S    3 - W
   *
   * 0x00 (falsch) steht für "nicht befahrbar", (wahr) für befahrbar */
  int distance;
  int visitedByDijkstra; // 0=nein,1=ja
  int vorgaengerx, vorgaengery;
} node[X_SIZE][Y_SIZE];

int token = 3;
hpointer knownNodes = NULL;
int nodeCount = 0;



void resetDistance(void) {
  int i, j;
  for(i = 0; i < X_SIZE; i++) {
    for(j = 0; j < Y_SIZE; j++) {
      node[i][j].distance = MAX_DISTANCE;
      node[i][j].visitedByDijkstra = 0;
    }
  }
}

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


void go(int startx, int starty, int zielx, int ziely, int simudx, int simudy)
{
  resetDistance();
  node[startx][starty].distance=0;
  
  int nodesRemaining = nodeCount;
  
  
  while(nodesRemaining>0)
  {
      int mindistance=MAX_DISTANCE;
      int minx,miny;
      
      // Knoten mit kleinster distance suchen
      hpointer temp=knownNodes;
      while(temp != NULL)
      {
        
      
      
        if (node[temp->x][temp->y].visitedByDijkstra==0)
        {
            if (node[temp->x][temp->y].distance < mindistance)
            {
              mindistance = node[temp->x][temp->y].distance;
              minx=temp->x;
              miny=temp->y;
            }
        }
        temp=temp->next;
      }
      
      int d;
      for(d=0;d<4;d++)
      {
        if (node[minx][miny].directions[d])
        {
            int mydistance=node[minx][miny].distance;
            int dx,dy;
            dirToXY(d,&dx,&dy);
            
            if (mydistance+1<node[minx+dx][miny+dy].distance)
            {
                node[minx+dx][miny+dy].distance=mydistance+1;
                node[minx+dx][miny+dy].vorgaengerx=minx;
                node[minx+dx][miny+dy].vorgaengery=miny;
            }
        }
      }
      
      node[minx][miny].visitedByDijkstra=1;
      nodesRemaining--;
      
      if (minx==zielx && miny==ziely)
        break;
  }
  
  
  // create way
  hpointer way = NULL;
  int tx=zielx,ty=ziely,ntx;
  while (tx!=startx||ty!=starty)
  {
    heap_push(tx,ty,&way);
    ntx=node[tx][ty].vorgaengerx;
    ty=node[tx][ty].vorgaengery;
    tx=ntx;
  }
  
  // follow way
  hpointer temp=way;
  while(temp != NULL)
  {
    Robot_Move(temp->x+simudx,temp->y+simudy);
    temp=temp->next;
  }
}


// return 1 if found one, 0 if there are no more
int findBacktrackNode(int *ox, int *oy, hpointer *heap)
{
    int x,y;
    while (heap_pop(&x,&y,heap))
    {
        int waysremaining = 0;
        
        int i;
        for(i = 0; i <= 3; i++) {
          if((node[x][y].directions[i]))
          {
            if(checkNodeAvailable(x, y, i))
            {
              waysremaining = 1;
              break;
            }
          }
        }
        
        if (waysremaining)
        {
            *ox = x;
            *oy = y;
            return 1;
        }
    }
    
    return 0;
}

void backToStart(int x, int y, int dx, int dy) {
  go(x,y,6,6,dx,dy);
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

    if (!heap_pop(&x,&y,&nextSteps)) // no given way
    {
        driveTo = 4; //
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
          backToStart(x, y, dx, dy);
          running = 0;
        }
    }
  }
	return EXIT_SUCCESS;
}
