#include "ennemies.h"
#include "environment.h"
#include "render.h"
#include "utils.h"

void move_enemy(enemy *enemy, int *is_player_dead)
{
    int r = enemy->row;
    int c = enemy->col;
    // gravity
    if (visited[min(r + 1, rows - 1)][c] != wall)
        enemy->row = min(r + 1, rows - 1);
    else
    {
        // move
        if (enemy->last_move == left)
        {
            // if there is a wall and nothing behind the enemy
            if ((visited[r][c - 1] == wall) && (visited[r][c + 1] != wall))
            {
                level[enemy->row][enemy->col] = ' ';
                visited[enemy->row][enemy->col] = unknown;
                enemy->col = enemy->col + 1;
                level[enemy->row][enemy->col] = 'e';
                visited[enemy->row][enemy->col] = entity;
                enemy->last_move = right;
            }
            // if there is not a wall
            else if (visited[r][c - 1] != wall)
            {
                level[enemy->row][enemy->col] = ' ';
                visited[enemy->row][enemy->col] = unknown;
                enemy->col = enemy->col - 1;
                level[enemy->row][enemy->col] = 'e';
                visited[enemy->row][enemy->col] = entity;
            }
        }
        else if (enemy->last_move == right)
        {
            // Same as before
            if ((visited[r][c - 1] != wall) && (visited[r][c + 1] == wall))
            {
                level[enemy->row][enemy->col] = ' ';
                visited[enemy->row][enemy->col] = unknown;
                enemy->col = enemy->col - 1;
                level[enemy->row][enemy->col] = 'e';
                visited[enemy->row][enemy->col] = entity;
                enemy->last_move = left;
            }
            else if (visited[r][c + 1] != wall)
            {
                level[enemy->row][enemy->col] = ' ';
                visited[enemy->row][enemy->col] = unknown;
                enemy->col = enemy->col + 1;
                level[enemy->row][enemy->col] = 'e';
                visited[enemy->row][enemy->col] = entity;
            }
        }
        else
        {
            if VERBOSE
            {
                printf("Not implemented : %d -> ", enemy->last_move);
                print_action(enemy->last_move);
            }
        }
    }

    // check if there is the player
    if (player_row == enemy->row && player_col == enemy->col)
    {
        *is_player_dead = 1;
    }
}

void move_ennemies(int *is_player_dead)
{
    for (int i = 0; i < nbr_ennemies; i++)
    {
        if (!ennemies[i].dead)
            move_enemy(ennemies + i, is_player_dead);
    }
}

void kill_enemy(int i)
{
    enemy *e = ennemies + i;
    if VERBOSE
        printf("Remove enemy %d", i);
    level[e->row][e->col] = ' ';
    visited[e->row][e->col] = unknown;
    e->dead = 1;
    // nbr_ennemies--;
}

void kill(int p_row, int p_col)
{
    for (int i = 0; i < nbr_ennemies; i++)
    {
        enemy *e = ennemies + i;
        if (e->row == p_row && e->col == p_col)
        {
            if VERBOSE
                printf("enemy found");
            kill_enemy(i);
        }
    }
}

void populate_ennemies()
{
    int cpt = 0;
    ennemies = malloc(sizeof(enemy) * nbr_ennemies);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == entity)
            {
                enemy *e = ennemies + cpt;
                e->row = i;
                e->col = j;
                e->last_move = left;
                e->dead = 0;
                cpt++;
            }
        }
    }
}