#include "qlearning.h"
#include "mazeEnv.h"
#include "functions.h"

void q_alloc()
{ // Make an array for all possible states
    qfunction = malloc(rows * cols * sizeof(double *));
    actions = 4;
    for (int i = 0; i < rows * cols; i++)
    {
        // For each state, there are limited possibilities of actions
        qfunction[i] = malloc(actions * sizeof(double));
    }
}

int qlearning(int row, int col)
{
    int *current = &visited[row][col];
    if (*current == goal)
    {
        return 1;
    }
    else if (*current == unknown)
    {
        *current = known;
    }
}

int main()
{
    maze_make("maze.txt");
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("number of actions : %d \n", number_actions);
}