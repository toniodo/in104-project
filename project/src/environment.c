#include "environment.h"

void alloc_level()
{
  level = malloc(rows * sizeof(char *));

  for (int i = 0; i < rows; i++)
  {
    level[i] = malloc(cols * sizeof(char *));
  }
}

void make_level(char *file_name)
{
  char c;
  char rows_s[3] = {'\0'};
  char cols_s[3] = {'\0'};
  int rows_i = 0;
  int cols_i = 0;
  int swap = 0;

  FILE *file = fopen(file_name, "r");

  if (file)
  {
    /* lire la premiere ligne avant EOF */
    while ((c = getc(file)) != EOF)
    {
      if (c == '\n')
      {
        break;
      }
      else if (c == ',')
      {
        swap = 1;
      }
      else if (!swap)
      {
        rows_s[rows_i] = c;
        rows_i++;
      }
      else
      {
        cols_s[cols_i] = c;
        cols_i++;
      }
    }
  }

  /* convertir le string en nombre */
  rows = atoi(rows_s);
  cols = atoi(cols_s);

  alloc_maze();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      c = getc(file);

      if (c == '\n')
      {
        c = getc(file);
      }
      else if (c == 's')
      {
        start_row = i;
        start_col = j;
      }
      else if (c == 'g')
      {
        goal_row = i;
        goal_col = j;
      }

      level[i][j] = c;
    }
  }

  fclose(file);
}

envOutput make_action(action a)
{
  double reward = 0;
  int done = 0;
  int dead = 0;
  int ennemy = 0;
  envOutput stepOut;

  int new_col = player_col;
  int new_row = player_row;

  switch (a)
  {
  case up:
    new_row = max(0, new_row - 1);
    break;

  case right:
    new_col = min(cols, new_col + 1);
    break;

  case left:
    new_col = max(0, new_col - 1);
    break;

  case up_left:
  case up_right:
  case nbr_actions:
  default:
  }

  int tile = visited[new_row][new_col];
  switch (tile)
  {
  case goal:
    reward = 1;
    done = 1;
    player_col = goal_col;
    player_row = goal_row;
    break;

  case wall:
    reward = -0.1;
    break;

  case crumb:
    reward = -0.01;
    player_col = new_col;
    player_row = new_row;
    break;

  default:
    // act like a discharge, force to explore
    reward = -0.01;
    player_col = new_col;
    player_row = new_row;
  }

  stepOut.reward = reward;
  stepOut.done = done;
  stepOut.dead = dead;
  stepOut.ennemy = ennemy;

  return stepOut;
}

void alloc_visited()
{
  visited = malloc(rows * sizeof(int *));
  int i;
  for (i = 0; i < rows; ++i)
  {
    visited[i] = malloc(cols * sizeof(int *));
  }
}

void init_visited()
{
  alloc_visited();

  int i, j;
  for (i = 0; i < rows; ++i)
  {
    for (j = 0; j < cols; ++j)
    {
      if (level[i][j] == '+')
      {
        visited[i][j] = wall;
      }
      else if (level[i][j] == 'g')
      {
        visited[i][j] = goal;
      }
      else
      {
        visited[i][j] = unknown;
      }
    }
  }
}