#include "ennemies.h"
#include "environment.h"

void move_ennemy(ennemy *ennemy)
{
    int en_row = ennemy->row;
    int en_col = ennemy->col;
    if (ennemy->last_move == left)
    {
        // if there is a wall and nothing behind the ennemy
        if ((visited[en_row][en_col - 1] == wall) && (visited[en_row][en_col + 1] != wall))
        {
            visited[ennemy->row][ennemy->col] = unknown;
            ennemy->col = ennemy->col + 1;
            visited[ennemy->row][ennemy->col] = entity;
            ennemy->last_move = right;
        }
        // if there is not a wall
        else if (visited[en_row][en_col - 1] != wall)
        {
            visited[ennemy->row][ennemy->col] = unknown;
            ennemy->col = ennemy->col - 1;
            visited[ennemy->row][ennemy->col] = entity;
        }
    }
    else if (ennemy->last_move == right)
    {
        // Same as before
        if ((visited[en_row][en_col - 1] != wall) && (visited[en_row][en_col + 1] == wall))
        {
            visited[ennemy->row][ennemy->col] = unknown;
            ennemy->col = ennemy->col - 1;
            visited[ennemy->row][ennemy->col] = entity;
            ennemy->last_move = left;
        }
        else if (visited[en_row][en_col + 1] != wall)
        {
            visited[ennemy->row][ennemy->col] = unknown;
            ennemy->col = ennemy->col + 1;
            visited[ennemy->row][ennemy->col] = entity;
        }
    }
    else
    {
        printf("Not implemented : %d", ennemy->last_move);
    }
    // Add the gravity effect
    while (visited[en_row + 1][en_col] != wall)
    {
        visited[ennemy->row][ennemy->col] = unknown;
        ennemy->row = ennemy->row + 1;
        visited[ennemy->row][ennemy->col] = entity;
    }
}

void move_ennemies()
{
    for (int i = 0; i < nbr_ennemies; i++)
    {
        move_ennemy(ennemies + i);
    }
}

void kill_ennemy(ennemy *ennemy)
{
    int ind = ennemy->index;
    for (int i = ind + 1; i < nbr_ennemies; i++)
    {
        ennemies[i - 1] = ennemies[i];
        (ennemies + i - 1)->index = i - 1;
    }
    free(ennemy);
    visited[ennemy->row][ennemy->col] = unknown;
    nbr_ennemies--;
}

void kill()
{
    int ind = 0;
    for (int i = 0; i < nbr_ennemies; i++)
    {
        if (((ennemies + i)->row == player_row) && ((ennemies + i)->col == player_col))
            ind = (ennemies + i)->index;
    }
    kill_ennemy(ennemies + ind);
}

void populate_ennemies()
{
    int cpt = nbr_ennemies;
    ennemies = malloc(sizeof(ennemy) * nbr_ennemies);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == entity)
            {
                (ennemies + cpt - 1)->row = i;
                (ennemies + cpt - 1)->col = j;
                (ennemies + cpt - 1)->last_move = true;
                (ennemies + cpt - 1)->index = cpt - 1;
                cpt--;
            }
        }
    }
}