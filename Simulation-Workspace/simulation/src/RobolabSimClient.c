#include "../h/Configuration.h"

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
  int x = 6, y = 0, a = 0, b = 0, driveTo, running = 1;

  initArray();

  while(running) {
    driveTo = 4;
    Robot_Move(a,b);
    printf("%d %d\n", a, b);
    node[x][y].state = 1;

    checkIntersection(x, y);

    int i;
    for(i = 0; i <= 3; i++) {
      if((node[x][y].directions[i]))
        if(checkNodeAvailable(x, y, i))
          driveTo = i;
    }

    switch(driveTo) {
      case 0:
        printf("Go NORTH\n");
        b++;
        y++;
        break;
      case 1:
        printf("Go EAST\n");
        a++;
        x++;
        break;
      case 2:
        printf("Go SOUTH\n");
        b--;
        y--;
        break;
      case 3:
        printf("Go WEST\n");
        a--;
        x--;
        break;
      case 4:
        printf("Labyrinth vollständig erkundet.\nEnde.\n");
        running = 0;
        break;
    }
  }

	return EXIT_SUCCESS;
}
