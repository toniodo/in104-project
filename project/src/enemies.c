#include "enemies.h"
#include "environment.h"
#include "render.h"
#include "utils.h"

void populate_enemies()
{
    int cpt = 0;
    enemies = malloc(sizeof(enemy) * nbr_enemies);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == entity)
            {
                enemy *e = enemies + cpt;
                e->row = i;
                e->col = j;
                e->last_move = left;
                e->dead = 0;
                cpt++;
            }
        }
    }
}

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
                printf("\n");
            }
        }
    }

    // check if there is the player
    if (player_row == enemy->row && player_col == enemy->col)
    {
        *is_player_dead = 1;
    }
}

void move_enemies(int *is_player_dead)
{
    for (int i = 0; i < nbr_enemies; i++)
    {
        if (!enemies[i].dead)
            move_enemy(enemies + i, is_player_dead);
    }
}

void kill_enemy(int i)
{
    enemy *e = enemies + i;
    if VERBOSE
        printf("Remove enemy %d", i);
    level[e->row][e->col] = ' ';
    visited[e->row][e->col] = unknown;
    e->dead = 1;
    // nbr_enemies--;
}

void kill()
{
    for (int i = 0; i < nbr_enemies; i++)
    {
        enemy *e = enemies + i;
        if (e->row == player_row && e->col == player_col)
        {
            if VERBOSE
                printf("enemy found");
            kill_enemy(i);
        }
    }
}

// return boolean
int is_enemy_near_player(int dist)
{
    int window = 0;
    // don't do that
    if (window)
    {
        // Look for a window around the player
        for (int i = -dist; i <= dist; i++)
        {
            for (int j = -dist; j <= dist; j++)
            {
                int r = player_row + i;
                int c = player_col + j;
                if (r < 0 || r >= rows || c < 0 || c >= cols)
                    break;
                if (visited[r][c] == entity)
                    return 1;
            }
        }
    }
    // better that for the moment
    else
    {
        if (visited[player_row][player_col - 1] == entity || visited[player_row][player_col + 1] == entity)
            return 1;
    }

    return 0;
}