#ifndef __ENNEMIES_H__
#define __ENNEMIES_H__

#include "environment.h"
struct enemy
{
  int row;
  int col;
  action last_move;
  int dead;
};

typedef struct enemy enemy;
int nbr_ennemies;
enemy *ennemies;

void move_ennemies(int *is_player_dead);
void move_enemy(enemy *enemy, int *is_player_dead);
void kill_enemy(int i);
void kill(int p_row, int p_col);
void populate_ennemies();

#endif