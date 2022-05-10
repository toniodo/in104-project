#ifndef __ENNEMIES_H__
#define __ENNEMIES_H__

struct ennemy
{
  int row;
  int col;
};

typedef struct ennemy ennemy;

ennemy *ennemies;

void move_ennemies();
void move_ennemy(ennemy *ennemy);

#endif