#include "render.h"

void level_render()
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      printf("%c ", level[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}
