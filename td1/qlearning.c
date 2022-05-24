#include "qlearning.h"
#include "mazeEnv.h"
#include "functions.h"
#include <time.h>
#include <stdbool.h>
#include "policies.h"

#define VERBOSE (true)

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
            qfunction[i][j] = ((float)rand()) / RAND_MAX / 100;
            // qfunction[i][j] = 0;
        }
    }
    // Set reward of goal
    qfunction[goal_row * cols + goal_col][0] = 0;
    qfunction[goal_row * cols + goal_col][1] = 0;
    qfunction[goal_row * cols + goal_col][2] = 0;
    qfunction[goal_row * cols + goal_col][3] = 0;
}

int qlearning()
{
    envOutput stepOutput;
    // initialisation of qlearning parameters
    // double eps = 0.1;
    double gamma = 0.8;
    double alpha = 0.8;
    int max_step = 100;
    // initialisation of a counter
    int cpt = 0;
    // initialisation index of start position
    state_row = start_row;
    state_col = state_col;
    int prev_state = state_from_pos(state_row, state_col);
    int new_state;
    // initialisation of action
    int act = 0;
    double reward = 0;
    while (cpt < max_step)
    {
        // save previous state
        prev_state = state_from_pos(state_row, state_col);
        // action according to policy
        act = policy_greedy(prev_state, qfunction[prev_state]);
        if VERBOSE
            printf("%d \n", (action)act);
        // printf("%d\n", act);
        //  response created by the action taken
        stepOutput = maze_step(act);
        reward = stepOutput.reward;
        // printf("J'ai gagné une récompense de %.2f\n", reward);
        new_state = state_from_pos(state_row, state_col);
        double update = alpha * (reward + gamma * maxlist(qfunction[new_state], number_actions, false) - qfunction[prev_state][act]);
        // printf("test : %.3f\n", update);
        // printf("%f\n", maxlist(qfunction[new_state], number_actions, true));
        qfunction[prev_state][act] = qfunction[prev_state][act] + update;
        // printf("\nNotre valeur de Q : %.2f", qfunction[prev_state][act]);
        //  printf("%f\n", qfunction[state][act]);
        //  printf("Le maximum des nouvelles actions vaut %f", maxlist(qfunction[new_state], number_actions,false));
        if (stepOutput.done)
        {
            printf("Je suis arrivé !\n");
            break;
        }
        //  actualisation of the visited matrix
        else
        {
            visited[stepOutput.new_row][stepOutput.new_col] = crumb;
        }
        cpt++;
        // show_matrix(qfunction, rows * cols - 1, number_actions);
    }
    printf("Le compteur : %d\n", cpt);
    return 1;
}

void add_crumbs()
{
    if VERBOSE
        printf("States :");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == crumb)
            {
                maze[i][j] = '.';
                if VERBOSE
                    printf("%d ", state_from_pos(i, j));
            }
        }
    }
    maze[start_row][start_col] = 's';
    printf("\n");
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
    maze_make("levels/maze.txt");

    // initialise qlearning matrix
    q_alloc();
    q_initialisation();
    if (VERBOSE)
    {
        printf("initial head of qfunction (random) :\n");
        show_matrix(qfunction, 20, number_actions);
    }

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
        if (VERBOSE)
        {
            // show full qmatrix
            /*
            printf("qfunction :\n")
            show_matrix(qfunction, state_from_pos(rows - 1, cols), number_actions);
            */
            // show head of qmatrix
            printf("head of qfunction :\n");
            printf("     up    down   left   right\n");
            show_matrix(qfunction, rows * cols - 1, number_actions);
        }
        maze_render();
        printf("%d %d", rows, cols);
        // waiting for action
        scanf("%c", &input);
    }
    return 0;
}