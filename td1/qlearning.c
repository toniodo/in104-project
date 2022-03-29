#include "qlearning.h"
#include "mazeEnv.h"
#include "functions.h"

void q_alloc()
{ // Make an array for all possible states
    qfunction = malloc(rows * cols * sizeof(double *));
    for (int i = 0; i < rows * cols; i++)
    {
        // For each state, there are limited possibilities of actions
        qfunction[i] = malloc(number_actions * sizeof(double));
    }
}

void q_initialisation()
{ // Initialisation random values
    for (int i = 0; i < rows * cols; i++)
    {
        for (int j = 0; j < number_actions; j++)
        {
            qfunction[i][j] = rand() / RAND_MAX;
        }
    }
    qfunction[goal_row * rows + goal_col][0] = 0;
    qfunction[goal_row * rows + goal_col][1] = 0;
    qfunction[goal_row * rows + goal_col][2] = 0;
    qfunction[goal_row * rows + goal_col][3] = 0;
}

int qlearning(int row, int col)
{
    int *current = &visited[row][col];
    switch (*current)
    {
    case goal:
        return 1;
    case unknown:
        *current = known;
    default:
        return 0;
    }
}

int main()
{
    srand(time(0));
    maze_make("maze.txt");
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("number of actions : %d \n", number_actions);
}