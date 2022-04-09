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

int state_from_pos(int row, int col)
{
    return row * cols + col;
}

int qlearning()
{
    envOutput stepOutput;
    double eps = 0.5;
    double gamma = 0.9;
    double alpha = 0.5;
    int max_step = 1000;
    int cpt = 0;
    int state = state_from_pos(start_row, start_col);
    int new_state;
    int act = 0;
    int reward = 0;
    while ((state != state_from_pos(goal_row, goal_col)) && cpt < max_step)
    {
        act = policy_greedy(state, eps);
        stepOutput = maze_step(act);
        reward = stepOutput.reward;
        new_state = state_from_pos(stepOutput.new_row, stepOutput.new_col);
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

void remove_crumbs()
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (maze[i][j] == '.')
            {
                maze[i][j] = ' ';
            }
        }
    }
}

int main()
{
    srand(time(0));
    // create maze from file
    maze_make("maze.txt");

    // initialise qlearning matrix
    q_alloc();
    q_initialisation();

    char input = 'y';
    // training loop, continue if y or enter pressed
    while (input == 'y' || input == '\n')
    {
        // initialise maze
        init_visited();
        maze_reset();
        remove_crumbs();
        // print maze
        printf("%d, %d \n", rows, cols);
        printf("number of actions : %d \n", number_actions);
        maze_render();
        // learn
        qlearning(rows, cols);
        // complete maze with crumbs and print it
        add_crumbs();
        maze_render();
        show_matrix(qfunction, state_from_pos(rows - 1, cols), number_actions);

        // waiting for action
        scanf("%c", &input);
    }
    return 0;
}