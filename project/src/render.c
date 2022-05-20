#include "render.h"
#include "agent.h"
#include <stdbool.h>
#include "utils.h"

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

void add_crumbs()
{
    if VERBOSE
        printf("States :");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == crumb)
            {
                level[i][j] = '.';
                if VERBOSE
                    printf("%d ", pos_from_coord(i, j));
            }
        }
    }
    level[start_row][start_col] = 's';
    printf("\n");
}

void remove_crumbs()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (level[i][j] == '.')
            {
                level[i][j] = ' ';
            }
        }
    }
}