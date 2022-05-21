#include "render.h"
#include "agent.h"
#include <stdbool.h>
#include "utils.h"

void level_render()
{
    if (!VERBOSE)
        for (int i = 0; i < 17; i++)
            printf("\n");

    if VERBOSE
    {
        printf("\n");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                printf("%d ", visited[i][j]);
            }
            printf("\n");
        }
        printf("\n\n\n");
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (i == player_row && j == player_col)
                printf("ç ");
            else
                printf("%c ", level[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void add_crumbs()
{
    /*
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
    */
    // level[player_row][player_col] = '@';
    if VERBOSE
        printf("%d ", pos_from_coord(player_row, player_col));

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

void print_action(action act)
{
    printf("%s\n", act == 0   ? "left"
                   : act == 1 ? "right"
                   : act == 2 ? "up"
                   : act == 3 ? "up_left"
                   : act == 4 ? "up_right"
                              : "falling");
}