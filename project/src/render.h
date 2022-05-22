#ifndef __RENDER_H__
#define __RENDER_H__

#include "environment.h"

enum render_type
{
  RenderPlayerPlayer, // player then player
  RenderPlayerEnnemy, // player then ennemy
  RenderEpochs        // render only after epochs
};

void start_render();
void level_render();

void add_crumbs();
void remove_crumbs();

void print_action(action act);

#endif