#include "mazeEnv.h"
#include "functions.h"
#include <time.h>
#include <stdbool.h>
#include "policies.h"
#include "2qlearning.h"

void q_alloc2()
{ // Make an array for all possible states
    qfunction1 = malloc(rows * cols * sizeof(double *));
    qfunction2 = malloc(rows * cols * sizeof(double *));
    for (int i = 0; i < rows * cols; i++)
    {
        // For each state, there are limited possibilities of actions
        qfunction1[i] = malloc(number_actions * sizeof(double));
        qfunction2[i] = malloc(number_actions * sizeof(double));
    }
}

void q_initialisation2()
{ // Initialisation random values
    for (int i = 0; i < rows * cols; i++)
    {
        for (int j = 0; j < number_actions; j++)
        {
            // qfunction[i][j] = ((float)rand()) / RAND_MAX;
            qfunction1[i][j] = 0;
            qfunction2[i][j] = 0;
        }
    }
    // Set reward of goal
    qfunction1[goal_row * cols + goal_col][0] = 0;
    qfunction1[goal_row * cols + goal_col][1] = 0;
    qfunction1[goal_row * cols + goal_col][2] = 0;
    qfunction1[goal_row * cols + goal_col][3] = 0;
    qfunction2[goal_row * cols + goal_col][0] = 0;
    qfunction2[goal_row * cols + goal_col][1] = 0;
    qfunction2[goal_row * cols + goal_col][2] = 0;
    qfunction2[goal_row * cols + goal_col][3] = 0;
}

int qlearning2()
{
    envOutput stepOutput;
    // initialisation of qlearning parameters
    double eps = 0.1;
    double gamma = 2;
    double alpha = 0.8;
    int max_step = 10000;
    // initialisation of a counter
    int cpt = 0;
    // initialisation index of start position
    state_row = start_row;
    state_col = state_col;
    int prev_state = state_from_pos(state_row, state_col);
    int new_state;
    // creation of temporary array
    double *array = malloc(sizeof(double) * number_actions);
    // initialisation of action
    int act = 0;
    double reward = 0;
    while (cpt < max_step)
    {
        // save previous state
        prev_state = state_from_pos(state_row, state_col);
        // sum of the two q-array
        for (int j = 0; j < number_actions; j++)
        {
            array[j] = qfunction2[prev_state][j] + qfunction1[prev_state][j];
        }
        // action according to policies
        act = policy_epsgreedy(prev_state, eps, array);
        // printf("%d\n", act);
        //  response created by the action taken
        stepOutput = maze_step(act);
        reward = stepOutput.reward;
        // printf("J'ai gagné une récompense de %.2f\n", reward);
        new_state = state_from_pos(state_row, state_col);
        int alea = rand() % 2;
        // actualisation with probability of 0.5
        if (alea)
        {
            qfunction1[prev_state][act] += alpha * (reward + gamma * maxlist(qfunction1[new_state], number_actions, false) - qfunction1[prev_state][act]);
        }
        else
        {
            qfunction2[prev_state][act] += alpha * (reward + gamma * maxlist(qfunction2[new_state], number_actions, false) - qfunction2[prev_state][act]);
        }
        // printf("test : %.3f\n", update);
        // printf("%f\n", maxlist(qfunction[new_state], number_actions, true));
        // printf("\nNotre valeur de Q : %.2f", qfunction[prev_state][act]);
        //  printf("%f\n", qfunction[state][act]);
        //  printf("Le maximum des nouvelles actions vaut %f", maxlist(qfunction[new_state], number_actions,false));
        if (stepOutput.done)
        {
            printf("Je suis arrivé !");
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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (visited[i][j] == crumb)
            {
                maze[i][j] = '.';
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
    maze_make("./levels/maze.txt");

    // initialise qlearning matrix
    q_alloc2();
    q_initialisation2();

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
        qlearning2(rows, cols);
        // complete maze with crumbs and print it
        add_crumbs();
        maze_render();
        // show full qmatrix
        /*
        printf("qfunction :\n")
        show_matrix(qfunction, state_from_pos(rows - 1, cols), number_actions);
        */
        /*// show head of qmatrix
        printf("head of qfunction :\n");
        printf("     up    down   left   right\n");
        show_matrix(qfunction, rows * cols - 1, number_actions);
        maze_render();
        printf("%d %d", rows, cols);*/
        // waiting for action
        scanf("%c", &input);
    }
    return 0;
}