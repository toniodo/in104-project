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
    // initialisation of a counter
    int cpt = 0;
    // initialisation index of start position
    player_row = start_row;
    player_col = start_col;
    int prev_state = state(player_row, player_col, 0);
    int new_state;
    // initialisation of action
    int act;
    double reward;
    // set input
    char input = 'y';
    while (cpt < max_step)
    {
        act = policy_greedy(prev_state, qfunction[prev_state]);
        if ((act == up_left) || (act == up_right))
        {
            state_up = prev_state;
            act_up = act;
        }
        // printf("%d\n", act);
        //  execute the previous action
        stepOutput = make_action(act);
        if (VERBOSE && render_type <= RenderPlayerPlayer)
        {
            printf("action taken : %d -> ", (action)act);
            print_action(act);
            printf("\n");
            print_q_matrix();
        }
        if (render_type <= RenderPlayerPlayer)
        {
            // add_crumbs();
            level_render(1);
            scanf("%c", &input);
            if (input == 'q')
                break;
        }
        reward = stepOutput.reward;
        // save new state
        new_state = state(player_row, player_col, stepOutput.enemy);
        // Observe reward
        // Using Sarsa
        qfunction[prev_state][act] += alpha * (reward + gamma * maxlist(qfunction[new_state], nbr_actions, false) - qfunction[prev_state][act]);

        if (stepOutput.done)
        {
            printf("Je suis arrivé !\n");
            break;
        }
        else if (stepOutput.dead)
        {
            if ((level[player_row][player_col] == 'd') && ((player_col <= 3 + (state_up % (rows * cols)) % cols) || (player_col >= -3 + (state_up % (rows * cols)) % cols)))
            {
                qfunction[state_up][act_up] += alpha * (-1 + gamma * maxlist(qfunction[new_state], nbr_actions, false) - qfunction[state_up][act_up]);
                printf("Y'a un trou !!!!");
            }

            printf("Game Over !\n");
            break;
        }
        //  actualisation of the visited matrix
        else
            visited[player_row][player_col] = crumb;
        cpt++;
        prev_state = new_state;
    }
    printf("Nombre total d'itérations : %d\n", cpt);
    return 1;
}
