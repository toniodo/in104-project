#include "ennemies.h"
#include "environment.h"
#include "render.h"
#include "utils.h"

void move_ennemy(ennemy *ennemy, int *is_player_dead)
{
    int r = ennemy->row;
    int c = ennemy->col;
    // gravity
    if (visited[min(r + 1, rows - 1)][c] != wall)
        ennemy->row = min(r + 1, rows - 1);
    else
    {
        // move
        if (ennemy->last_move == left)
        {
            // if there is a wall and nothing behind the ennemy
            if ((visited[r][c - 1] == wall) && (visited[r][c + 1] != wall))
            {
                level[ennemy->row][ennemy->col] = ' ';
                visited[ennemy->row][ennemy->col] = unknown;
                ennemy->col = ennemy->col + 1;
                level[ennemy->row][ennemy->col] = 'e';
                visited[ennemy->row][ennemy->col] = entity;
                ennemy->last_move = right;
            }
            // if there is not a wall
            else if (visited[r][c - 1] != wall)
            {
                level[ennemy->row][ennemy->col] = ' ';
                visited[ennemy->row][ennemy->col] = unknown;
                ennemy->col = ennemy->col - 1;
                level[ennemy->row][ennemy->col] = 'e';
                visited[ennemy->row][ennemy->col] = entity;
            }
        }
        else if (ennemy->last_move == right)
        {
            // Same as before
            if ((visited[r][c - 1] != wall) && (visited[r][c + 1] == wall))
            {
                level[ennemy->row][ennemy->col] = ' ';
                visited[ennemy->row][ennemy->col] = unknown;
                ennemy->col = ennemy->col - 1;
                level[ennemy->row][ennemy->col] = 'e';
                visited[ennemy->row][ennemy->col] = entity;
                ennemy->last_move = left;
            }
            else if (visited[r][c + 1] != wall)
            {
                level[ennemy->row][ennemy->col] = ' ';
                visited[ennemy->row][ennemy->col] = unknown;
                ennemy->col = ennemy->col + 1;
                level[ennemy->row][ennemy->col] = 'e';
                visited[ennemy->row][ennemy->col] = entity;
            }
        }
        else
        {
            printf("Not implemented : %d -> ", ennemy->last_move);
            print_action(ennemy->last_move);
        }
    }

    // check if there is the player
    if (player_row == ennemy->row && player_col == ennemy->col)
    {
        *is_player_dead = 1;
    }
}

void move_ennemies(int *is_player_dead)
{
    for (int i = 0; i < nbr_ennemies; i++)
    {
        move_ennemy(ennemies + i, is_player_dead);
    }
}

void kill_ennemy(int i)
{
    ennemy *e = ennemies + i;
    level[e->row][e->col] = ' ';
    visited[e->row][e->col] = unknown;
    for (int j = i + 1; j < nbr_ennemies; j++)
        ennemies[i - 1] = ennemies[i];
    nbr_ennemies--;
}

void kill(int p_row, int p_col)
{
    for (int i = 0; i < nbr_ennemies; i++)
    {
        ennemy *e = ennemies + i;
        if (e->row == p_row && e->col == p_col)
        {
            printf("ennemy found");
            kill_ennemy(i);
        }
    }
}

void populate_ennemies()
{
    int cpt = 0;
    ennemies = malloc(sizeof(ennemy) * nbr_ennemies);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == entity)
            {
                ennemy *e = ennemies + cpt;
                e->row = i;
                e->col = j;
                e->last_move = left;
                cpt++;
            }
        }
    }
}