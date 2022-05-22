#ifndef __RENDER_H__
#define __RENDER_H__

#include "environment.h"

enum render_type
{
  RenderPlayerEnemy,  // player then enemy
  RenderPlayerPlayer, // player then player
  RenderEpochs        // render only after epochs
};

enum render_type render_type;

void start_render();
void level_render(int padding);

void add_crumbs();
void remove_crumbs();

void print_action(action act);

#endif