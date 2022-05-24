#include "mazeEnv.h"

int dfs(int row, int col)
{
    int *current = &visited[row][col];

    if (*current == goal)
    {
        return 1;
    }
    else if (*current == unknown)
    {
        *current = known;

        if (dfs(row, col - 1))
        {
            *current = crumb;
            return 1;
        }
        else if (dfs(row + 1, col))
        {
            *current = crumb;
            return 1;
        }
        else if (dfs(row, col + 1))
        {
            *current = crumb;
            return 1;
        }
        else if (dfs(row - 1, col))
        {
            *current = crumb;
            return 1;
        }
    }

    return 0;
}

void add_crumbs()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == crumb)
            {
                maze[i][j] = '.';
            }
        }
    }
    maze[start_row][start_col] = 's';
}

int main()
{
    maze_make("./levels/maze.txt");
    init_visited();

    printf("%d, %d \n", rows, cols);
    printf("number of actions :  %d \n", number_actions);
    maze_render();
    dfs(start_row, start_col);
    add_crumbs();
    maze_render();
    return 0;
}
