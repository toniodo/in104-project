#include "qlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include <time.h>

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
            qfunction[i][j] = ((float)rand()) / RAND_MAX / 2.;
        }
    }
    // Set reward of goal
    qfunction[goal_row * cols + goal_col][0] = 0;
    qfunction[goal_row * cols + goal_col][1] = 0;
    qfunction[goal_row * cols + goal_col][2] = 0;
    qfunction[goal_row * cols + goal_col][3] = 0;
}

int policy_max(int state)
{
    return imaxlist(qfunction[state], number_actions);
}

int policy_greedy(int state, float epsi)
{
    int actio = 0;
    float alea = ((float)rand()) / RAND_MAX;
    if (alea > (1 - epsi))
    {
        actio = env_action_sample();
    }
    else
    {
        actio = imaxlist(qfunction[state], number_actions);
    }
    return actio;
}

int qlearning()
{
    envOutput stepOutput;
    double eps = 0.5;
    double gamma = 0.9;
    double alpha = 0.5;
    int max_step = 1000;
    int cpt = 0;
    int state = start_row * cols + start_col;
    int new_state = state;
    int act = 0;
    int reward = 0;
    while ((state != goal_row * cols + goal_col) && cpt < max_step)
    {
        act = policy_greedy(state, eps);
        stepOutput = maze_step(act);
        reward = stepOutput.reward;
        new_state = stepOutput.new_row * cols + stepOutput.new_col;
        qfunction[state][act] += alpha * (reward + gamma * maxlist(qfunction[new_state], number_actions) - qfunction[state][act]);
        // printf("%f\n", qfunction[state][act]);
        state = new_state;
        visited[stepOutput.new_row][stepOutput.new_col] = crumb;
        cpt++;
    }
    return 1;
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
    srand(time(0));
    maze_make("maze.txt");
    int initialised = 0;
    char input = 'y';

    // training loop
    while (input == 'y' || input == '\n')
    {
        init_visited();
        maze_reset();
        printf("%d, %d \n", rows, cols);
        printf("number of actions : %d \n", number_actions);
        maze_render();
        if (!initialised)
        {
            q_alloc();
            q_initialisation();
            initialised = 1;
        }
        qlearning(rows, cols);
        add_crumbs();
        maze_render();

        // pause
        scanf("%c", &input);
    }
    return 0;
}