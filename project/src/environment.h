#ifndef __ENV_H__
#define __ENV_H__

#include "agent.h"
#include <stdlib.h>
#include <stdio.h>

char **level;
int **visited;
int rows;
int cols;

// Start position
int start_row;
int start_col;

// Goal position
int goal_row;
int goal_col;

// Player position
int player_row;
int player_col;

enum terrain
{
  unknown,
  wall,
  start,
  goal,
  entity,
  death,
  teleporter1,
  teleporter2,
  crumb
};

typedef enum terrain terrain;

/* 5 actions possible*/
/* nbr_actions: number of actions*/
enum action
{
  left,
  right,
  up,
  up_left,
  up_right,
  nbr_actions
};

typedef enum action action;

// Environment variables
action previous_action;

// environment answer
struct envOutput
{
  double reward;
  int done;
  int dead;
  int ennemy;
};

typedef struct envOutput envOutput;

// allocate level matrix
void alloc_level();
void alloc_visited();
// create level from file
void make_level(char *);
void init_visited();
void reset_level();
// make action to the environment
envOutput make_action(action a);
void gravity(int *new_row, int *new_col);

#endif