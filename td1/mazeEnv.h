#ifndef MAZEENV_H
#define MAZEENV_H

#include <stdio.h>
#include <stdlib.h>

char **maze;
int **visited;
int rows;
int cols;

/*Coordonnées position départ */
int start_row;
int start_col;
int state_row;
int state_col;

/*Coordonnées position arrivée */
int goal_row;
int goal_col;

enum terrain
{
  unknown,
  wall,
  known,
  goal,
  crumb
};
/* 4 actions possibles dans un labyrinthe*/
/* number_actions: obtenir le nombre total d'actions possibles*/
enum action
{
  up,
  down,
  left,
  right,
  number_actions
};

typedef enum action action;

/* output of an agent : new state s'*/
struct envOutput
{
  int new_col;
  int new_row;
  double reward;
  int done;
};

typedef struct envOutput envOutput;

void alloc_maze();

/*Creer un tableau pour représenter un labyrinthe à partir d'un fichier*/
void maze_make(char *);

/*afficher un labyrinthe sur un terminal*/
void maze_render();

/*remettre l'agent à la position initiale*/
void maze_reset();

/*executer une action a et observer la récompense et le nouvel état*/
envOutput maze_step(action a);

/*Choisir une action au hasard */
action env_action_sample();

void alloc_visited();

void init_visited();

#endif /* MAZEENV_H */
