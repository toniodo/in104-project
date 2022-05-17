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
  // create maze from file
  make_level("./levels/base.txt");

  // initialise qlearning matrix
  alloc_level();
  alloc_maze();
  // printf("initial head of qfunction (random) :\n");
  // show_matrix(qfunction, 20, number_actions);

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
    // show full qmatrix
    /*
    printf("qfunction :\n")
    show_matrix(qfunction, state_from_pos(rows - 1, cols), number_actions);
    */
    // show head of qmatrix
    // printf("head of qfunction :\n");
    // printf("     up    down   left   right\n");
    // show_matrix(qfunction, rows * cols - 1, nbr_actions);
    // maze_render();
    // printf("%d %d", rows, cols);
    // waiting for action
    scanf("%c", &input);
  }
  return 0;
}