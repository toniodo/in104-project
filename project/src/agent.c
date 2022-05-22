#include "agent.h"
#include "environment.h"
#include "utils.h"
#include "policies.h"
#include "render.h"

void q_alloc()
{ // Make an array for all possible states (position with presence of enemy)
    qfunction = malloc(rows * cols * 2 * sizeof(double *));
    for (int i = 0; i < rows * cols * 2; i++)
    {
        // For each state, there are limited possibilities of actions
        qfunction[i] = malloc(nbr_actions * sizeof(double));
    }
}

void q_initialisation()
{ // Initialisation random values
    for (int i = 0; i < rows * cols * 2; i++)
    {
        for (int j = 0; j < nbr_actions; j++)
        {
            qfunction[i][j] = ((float)rand()) / RAND_MAX / 100;
            // qfunction[i][j] = 0;
        }
    }
    // Set reward of goal
    for (int i = 0; i < 4; i++)
    {
        qfunction[goal_row * cols + goal_col][i] = 0;
        qfunction[rows * cols + goal_row * cols + goal_col][i] = 0;
    }
}

int make_epoch()
{
    envOutput stepOutput;
    // initialisation of qlearning parameters
    // double eps = 0.1;
    double gamma = 0.8;
    double alpha = 0.8;
    int max_step = 200;
    bool enemies = false;
    // initialisation of a counter
    int cpt = 0;
    // initialisation index of start position
    player_row = start_row;
    player_col = start_col;
    int prev_state = state(enemies);
    int new_state;
    // initialisation of action
    int act = policy_greedy(prev_state, qfunction[prev_state]);
    int new_act;
    double reward;
    // set input
    char input = 'y';
    while (cpt < max_step)
    {
        // printf("%d\n", act);
        //  execute the previous action
        stepOutput = make_action(act);
        if VERBOSE
        {
            printf("action taken : %d -> ", (action)act);
            print_action(act);
        }
        if (render_type <= RenderPlayerPlayer)
        {
            // add_crumbs();
            level_render(1);
            scanf("%c", &input);
            if (input == 'q')
                break;
        }
        // save new state
        new_state = state(enemies);
        // Observe reward
        reward = stepOutput.reward;
        // choose action according to policy
        new_act = policy_greedy(new_state, qfunction[new_state]);
        // Using Sarsa
        qfunction[prev_state][act] += alpha * (reward + gamma * qfunction[new_state][new_act] - qfunction[prev_state][act]);

        if (stepOutput.done)
        {
            printf("Je suis arrivé !\n");
            break;
        }
        else if (stepOutput.dead)
        {
            printf("Game Over !\n");
            break;
        }
        //  actualisation of the visited matrix
        else
            visited[player_row][player_col] = crumb;
        cpt++;
        enemies = stepOutput.enemy;
        act = new_act;
        prev_state = new_state;
        // show_matrix(qfunction, rows * cols - 1, nbr_actions);
    }
    printf("Nombre total d'itérations : %d\n", cpt);
    return 1;
}
