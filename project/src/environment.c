#include "environment.h"
#include "enemies.h"
#include "utils.h"
#include "render.h"

void alloc_level()
{
  level = malloc(rows * sizeof(char *));

  for (int i = 0; i < rows; i++)
  {
    level[i] = malloc(cols * sizeof(char *));
  }
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
// TODO: Extend to env
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

  alloc_level();

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      switch (c = getc(file))
      {
      case '\n':
        c = getc(file);
        break;
      case 's':
        start_row = i;
        start_col = j;
        break;
      case 'g':
        goal_row = i;
        goal_col = j;
        break;
      }

      level[i][j] = c;
    }
  }
  fclose(file);
}

void init_visited()
{
  alloc_visited();
  nbr_enemies = 0;

  int i, j;
  for (i = 0; i < rows; ++i)
  {
    for (j = 0; j < cols; ++j)
    {
      switch (level[i][j])
      {
      case '+':
        visited[i][j] = wall;
        break;
      case 'g':
        visited[i][j] = goal;
        break;
      case 's':
        visited[i][j] = start;
        break;
      case 'e':
        visited[i][j] = entity;
        nbr_enemies++;
        break;
      case 'd':
        visited[i][j] = death;
        break;
      case '1':
        visited[i][j] = teleporter1;
        break;
      case '2':
        visited[i][j] = teleporter2;
        break;
      default:
        visited[i][j] = unknown;
      }
    }
  }

  populate_enemies();
}

// need allocations before
void reset_level()
{
  make_level(LEVEL);
  init_visited();
  player_row = start_row;
  player_col = start_col;
}

// TODO :
// implement gravity
// implement all reactions
envOutput make_action(action a)
{
  //------------
  // Player turn
  //------------
  double reward = 0;
  int done = 0;
  int dead = 0;
  envOutput stepOut;

  int new_col = player_col;
  int new_row = player_row;

  // look downward
  if (visited[min(rows - 1, new_row + 1)][new_col] != wall)
    gravity(&new_row, &new_col);
  else
  {
    // Move
    switch (a)
    {
    case up:
      new_row = max(0, new_row - 1);
      break;

    case up_left:
      // up + falling through
      new_row = max(0, new_row - 1);
    case left:
      new_col = max(0, new_col - 1);
      break;

    case up_right:
      // up + falling through
      new_row = max(0, new_row - 1);
    case right:
      new_col = min(cols - 1, new_col + 1);
      break;

    default:
      break;
    }
    previous_action = a;
  }

  int tile = visited[new_row][new_col];
  if (VERBOSE && render_type <= RenderPlayerPlayer)
    printf("tile : %d\n", tile);
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

  case entity:
    if (VERBOSE)
      printf("Encounter entity\n");
    // kill -> break, but death -> fall through
    if (previous_action == nbr_actions)
    {
      reward = 0.5;
      player_col = new_col;
      player_row = new_row;
      printf("Goomba killed !\n");
      kill();
      break;
    }
  case death:
    dead = 1;
    reward = -1;
    player_col = new_col;
    player_row = new_row;
  case teleporter1:
    reward = 0.5;
    player_col = new_col;
    player_row = new_row;
  case teleporter2:
  case crumb:
  default:
    // act like a discharge, force to explore
    reward = linear_reward(-0.1, 0, cols, new_col);
    player_col = new_col;
    player_row = new_row;
  }

  if (!dead && nbr_enemies)
  {
    if (render_type == RenderPlayerEnemy)
    {
      printf("\n");
      level_render(1);
      char input;
      scanf("%c", &input);
    }

    //------------
    // Environment turn
    //------------

    int is_player_dead = 0;
    move_enemies(&is_player_dead);
    if (is_player_dead)
    {
      reward -= 1;
      dead = 1;
    }
  }
  //------------
  // END
  //------------

  // Check if ennemy is near

  stepOut.reward = reward;
  stepOut.done = done;
  stepOut.dead = dead;
  stepOut.enemy = is_enemy_near_player(1);

  return stepOut;
}

void gravity(int *new_row, int *new_col)
{
  int r = min(rows - 1, *new_row + 1);
  int c;
  switch (previous_action)
  {
  case up_left:
    c = max(0, *new_col - 1);
    if (visited[r][c] == wall)
    {
      if (visited[*new_row][c] == wall)
        *new_row = r;
      else
        *new_col = c;
    }
    // else if (dest == teleporter1)
    // else if (dest == teleporter2)
    else
    {
      *new_col = c;
      *new_row = r;
    }
    break;
  case up_right:
    c = min(cols - 1, *new_col + 1);
    if (visited[r][c] == wall)
    {
      if (visited[*new_row][c] == wall)
        *new_row = r;
      else
        *new_col = c;
    }
    // else if (dest == teleporter1)
    // else if (dest == teleporter2)
    else
    {
      *new_col = c;
      *new_row = r;
    }
    break;

  // case free fall
  default:
    *new_row = r;
    break;
  }
  // free fall
  if (VERBOSE && render_type <= RenderPlayerPlayer)
    printf("falling\n");
  previous_action = nbr_actions;
}

double linear_reward(double min_reward, double max_reward, int N, int val)
{
  double step = (max_reward - min_reward) / (double)N;
  return min_reward + step * val;
}
