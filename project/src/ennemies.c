#include "ennemies.h"

void move_ennemy(ennemy *ennemy)
{
    int en_row = ennemy->row;
    int en_col = ennemy->col;
    if (ennemy->last_move == left)
    {
        // if there is a wall and nothing behind the ennemy
        if ((level[en_row][en_col - 1] == '+') && (level[en_row][en_col + 1] != '+'))
        {
            ennemy->col = ennemy->col + 1;
            ennemy->last_move = right;
        }
        // if there is not a wall
        if
            else(level[en_row][en_col - 1] != '+')
            {
                ennemy->col = ennemy->col - 1;
            }
    }
    else if (ennemy->last_move == right)
    {
        // Same as before
        if ((level[en_row][en_col - 1] != '+') && (level[en_row][en_col + 1] == '+'))
        {
            ennemy->col = ennemy->col - 1;
            ennemy->last_move = left;
        }
        if
            else(level[en_row][en_col + 1] != '+')
            {
                ennemy->col = ennemy->col + 1;
            }
    }
    else
    {
        printf("Not implemented : %d", *ennemy->last_move);
    }
    // Add the gravity effect
    while (level[en_row + 1][en_col] != '+')
    {
        ennemy->row = ennemy->row + 1;
    }
}