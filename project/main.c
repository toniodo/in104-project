#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "./src/agent.h"
#include "./src/environment.h"
#include "./src/render.h"

int main(int argc, char *argv[])
{
  // initialize time
  srand(time(0));
  reset_level();
  start_render();
  q_alloc();
  q_initialisation();
  char input = 'y';
  // training loop, continue if y or enter pressed
  while (input == 'y' || input == '\n')
  {
    // initialise maze
    init_visited();
    reset_level();
    remove_crumbs();
    // print maze
    if VERBOSE
    {
      printf("rows %d | cols %d \n", rows, cols);
      printf("number of actions : %d \n", nbr_actions);
    }
    // level_render();
    //  learn
    make_epoch();
    // complete maze with crumbs and print it
    // add_crumbs();
    level_render();
    // Waiting for an action
    scanf("%c", &input);
  }
  return 0;
}