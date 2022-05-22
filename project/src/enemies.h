#ifndef __enemies_H__
#define __enemies_H__

#include "environment.h"
struct enemy
{
  int row;
  int col;
  action last_move;
  int dead;
};

typedef struct enemy enemy;
int nbr_enemies;
enemy *enemies;

void populate_enemies();
void move_enemies(int *is_player_dead);
void move_enemy(enemy *enemy, int *is_player_dead);
void kill_enemy(int i);
void kill();
int is_enemy_near_player(int dist);

#endif