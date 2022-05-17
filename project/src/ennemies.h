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

void move_ennemies();
void move_ennemy(ennemy *ennemy);

#endif