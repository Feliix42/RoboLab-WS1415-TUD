#include "../h/Configuration.h"
#include "../h/heap.h"

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
} node[13][7];



void initArray(void) {
  int i, j;
  for(i = 0; i < 13; i++) {
    for(j = 0; j < 7; j++) {
      node[i][j].state = 2;
    }
  }
}


void checkIntersection(int x, int y) {
  if (node[x][y].state == 1)
    return;

  int intersection = Robot_GetIntersections();

  if(intersection & NORTH) {
    node[x][y].directions[0] = 0x01;
    if(node[x][y+1].state != 1)
      node[x][y+1].state = 0;
  } else {
    node[x][y].directions[0] = 0x00;
    if((node[x][y+1].state != 0) && (node[x][y+1].state != 1))
      node[x][y+1].state = 2;
  }


  if(intersection & EAST) {
    node[x][y].directions[1] = 0x01;
    if(node[x+1][y].state != 1)
      node[x+1][y].state = 0;
  } else {
    node[x][y].directions[1] = 0x00;
    if((node[x+1][y].state != 0) && (node[x+1][y].state != 1))
      node[x+1][y].state = 2;
  }

  if(intersection & SOUTH) {
    node[x][y].directions[2] = 0x01;
    if(node[x][y-1].state != 1)
      node[x][y-1].state = 0;
  } else {
    node[x][y].directions[2] = 0x00;
    if((node[x][y-1].state != 0) && (node[x][y-1].state != 1))
      node[x][y-1].state = 2;
  }


  if(intersection & WEST) {
    node[x][y].directions[3] = 0x01;
    if(node[x-1][y].state != 1)
      node[x-1][y].state = 0;
  } else {
    node[x][y].directions[3] = 0x00;
    if((node[x-1][y].state != 0) && (node[x-1][y].state != 1))
      node[x-1][y].state = 2;
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


int main(void) {
  int x = 6, y = 0, driveTo, running = 1;

  int dx = -6, dy = 0;
  
  initArray();
  
  Robot_Move(a,b);

  while(running) {
    printf("%d %d\n", x+dx, y+dy);

    checkIntersection(x, y);

    node[x][y].state = 1;

    driveTo = 4; //
    int i;
    for(i = 0; i <= 3; i++) {
      if((node[x][y].directions[i]))
        if(checkNodeAvailable(x, y, i))
          driveTo = i;
    }
    
    switch(driveTo) {
      case 0:
        printf("Go NORTH\n");
        y++;
        heap_push(x,y);
        break;
      case 1:
        printf("Go EAST\n");
        x++;
        heap_push(x,y);
        break;
      case 2:
        printf("Go SOUTH\n");
        y--;
        heap_push(x,y);
        break;
      case 3:
        printf("Go WEST\n");
        x--;
        heap_push(x,y);
        break;
      case 4:
        if (heap_pop(&x,&y))
        {
            printf("going back");
        }
        else
        {
            printf("Labyrinth vollständig erkundet.\nEnde.\n");
            running = 0;
        }
        break;
    }
    
    Robot_Move(x+dx,y+dy);
  }

	return EXIT_SUCCESS;
}
