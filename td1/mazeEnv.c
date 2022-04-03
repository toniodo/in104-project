#include "mazeEnv.h"
#include "functions.h"

void alloc_maze()
{
    maze = malloc(rows * sizeof(char *));

    for (int i = 0; i < rows; i++)
    {
        maze[i] = malloc(cols * sizeof(char *));
    }
}

void maze_make(char *file_name)
{
    char c;
    char rows_s[3] = {'\0'};
    char cols_s[3] = {'\0'};
    int rows_i = 0;
    int cols_i = 0;
    int swap = 0;

    FILE *file = fopen(file_name, "r");

    if (file)
    {
        /* lire la premiere ligne avant EOF */
        while ((c = getc(file)) != EOF)
        {
            if (c == '\n')
            {
                break;
            }
            else if (c == ',')
            {
                swap = 1;
            }
            else if (!swap)
            {
                rows_s[rows_i] = c;
                rows_i++;
            }
            else
            {
                cols_s[cols_i] = c;
                cols_i++;
            }
        }
    }

    /* convertir le string en nombre */
    rows = atoi(rows_s);
    cols = atoi(cols_s);

    alloc_maze();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            c = getc(file);

            if (c == '\n')
            {
                c = getc(file);
            }
            else if (c == 's')
            {
                start_row = i;
                start_col = j;
            }
            else if (c == 'g')
            {
                goal_row = i;
                goal_col = j;
            }

            maze[i][j] = c;
        }
    }

    fclose(file);
}

void maze_render()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void maze_reset()
{
    state_row = start_row;
    state_col = start_col;
}

envOutput maze_step(action a)
{
    int reward = 0;
    int done = 0;
    envOutput stepOut;

    int new_cols = state_col;
    int new_rows = state_row;

    switch (a)
    {
    case up:
        new_rows = max(0, state_row - 1);
        break;

    case down:
        new_rows = min(rows, state_row + 1);
        break;

    case right:
        new_cols = min(cols, state_col + 1);
        break;

    case left:
        new_cols = max(0, state_col - 1);
        break;

    case number_actions:
    default:
        break;
    }

    if (visited[new_rows][new_cols] == goal)
    {
        reward = 1;
        done = 1;
        state_col = new_cols;
        state_row = new_rows;
        stepOut.new_col = state_col;
        stepOut.new_row = state_row;
    }

    else if (visited[new_rows][new_cols] == wall)
    {
        reward = -1;
        stepOut.new_col = state_col;
        stepOut.new_row = state_row;
    }

    else if (visited[new_rows][new_cols] == crumb)
    {
        reward = -0.01;
        state_col = new_cols;
        state_row = new_rows;
        stepOut.new_col = state_col;
        stepOut.new_row = state_row;
    }

    else
    {
        reward = 0.1;
        state_col = new_cols;
        state_row = new_rows;
        stepOut.new_col = state_col;
        stepOut.new_row = state_row;
    }

    stepOut.reward = reward;
    stepOut.done = done;

    return stepOut;
}

action env_action_sample()
{
    return (enum action)(rand() % number_actions);
}

void alloc_visited()
{
    visited = malloc(rows * sizeof(int *));
    int i;
    for (i = 0; i < rows; ++i)
    {
        visited[i] = malloc(cols * sizeof(int *));
    }
}

void init_visited()
{
    alloc_visited();

    int i, j;
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            if (maze[i][j] == '+')
            {
                visited[i][j] = wall;
            }
            else if (maze[i][j] == 'g')
            {
                visited[i][j] = goal;
            }
            else
            {
                visited[i][j] = unknown;
            }
        }
    }
}
