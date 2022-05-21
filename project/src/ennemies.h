#ifndef __ENNEMIES_H__
#define __ENNEMIES_H__

#include "environment.h"
struct ennemy
{
  int row;
  int col;
  action last_move;
};

typedef struct ennemy ennemy;
int nbr_ennemies;
ennemy *ennemies;

void move_ennemies(int *is_player_dead);
void move_ennemy(ennemy *ennemy, int *is_player_dead);
void kill_ennemy(int i);
void kill(int p_row, int p_col);
void populate_ennemies();

#endif