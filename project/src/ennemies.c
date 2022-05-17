#include "ennemies.h"

void move_ennemy(ennemy *ennemy)
{
    int en_row = ennemy->row;
    int en_col = ennemy->col;
    if (ennemy->last_move == left)
    {
        // if there is a wall and nothing behind the ennemy
        if ((visited[en_row][en_col - 1] == wall) && (visited[en_row][en_col + 1] != wall))
        {
            ennemy->col = ennemy->col + 1;
            ennemy->last_move = right;
        }
        // if there is not a wall
        else if (visited[en_row][en_col - 1] != wall)
        {
            ennemy->col = ennemy->col - 1;
        }
    }
    else if (ennemy->last_move == right)
    {
        // Same as before
        if ((visited[en_row][en_col - 1] != wall) && (visited[en_row][en_col + 1] == wall))
        {
            ennemy->col = ennemy->col - 1;
            ennemy->last_move = left;
        }
        else if (visited[en_row][en_col + 1] != wall)
        {
            ennemy->col = ennemy->col + 1;
        }
    }
    else
    {
        printf("Not implemented : %d", ennemy->last_move);
    }
    // Add the gravity effect
    while (visited[en_row + 1][en_col] != wall)
    {
        ennemy->row = ennemy->row + 1;
    }
}

void move_ennemies()
{
    for (int i = 0; i < nbr_ennemies; i++)
    {
        move_ennemy(ennemies + i);
    }
}