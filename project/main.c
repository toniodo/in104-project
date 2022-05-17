#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "./src/agent.h"
#include "./src/environment.h"

int main(int argc, char *argv[])
{
  // initialize time
  srand(time(0));
  // allocate
  alloc_level();
  alloc_visited();
  maze_reset();
  maze_render();
  char input = 'y';
  // training loop, continue if y or enter pressed
  while (input == 'y' || input == '\n')
  {
    // initialise maze
    init_visited();
    maze_reset();
    remove_crumbs();
    // print maze
    printf("%d, %d \n", rows, cols);
    printf("number of actions : %d \n", nbr_actions);
    maze_render();
    // learn
    qlearning(rows, cols);
    // complete maze with crumbs and print it
    add_crumbs();
    maze_render();
    // Waiting for an action
    scanf("%c", &input);
  }
  return 0;
}