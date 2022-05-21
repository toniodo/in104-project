#include "agent.h"
#include "environment.h"
#include "utils.h"
#include "policies.h"
#include "render.h"

void q_alloc()
{ // Make an array for all possible states (position with presence of ennemy)
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
    bool ennemies = false;
    // initialisation of a counter
    int cpt = 0;
    // initialisation index of start position
    player_row = start_row;
    player_col = start_col;
    int prev_pos = pos_from_coord(player_row, player_col);
    int new_state;
    // initialisation of action
    int act = 0;
    int prev_act = act;
    double reward = 0;
    // set input
    char input = 'y';
    while (cpt < max_step)
    {
        // printf("%d\n", act);
        //  execute the previous action
        stepOutput = make_action(prev_act);
        if VERBOSE
        {
            printf("%d \n", (action)act);
            add_crumbs();
            level_render();
            scanf("%c", &input);
            if (input == 'q')
                break;
        }
        // save previous state
        new_state = pos_from_coord(player_row, player_col);
        // Consider the presence of an ennemy
        if (ennemies)
            new_state = rows * cols + new_state;
        // choose action according to policy
        act = policy_greedy(new_state, qfunction[new_state]);
        reward = stepOutput.reward;
        // printf("J'ai gagné une récompense de %.2f\n", reward);
        new_state = state(ennemies);
        // printf("test : %.3f\n", update);
        // printf("%f\n", maxlist(qfunction[new_state], nbr_actions, true));
        // Using Sarsa
        qfunction[prev_pos][act] += alpha * (reward + gamma * qfunction[new_state][new_state] - qfunction[prev_pos][act]);
        // printf("\nNotre valeur de Q : %.2f", qfunction[prev_pos][act]);
        //  printf("%f\n", qfunction[state][act]);
        //  printf("Le maximum des nouvelles actions vaut %f", maxlist(qfunction[new_state], nbr_actions,false));
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
        {
            visited[player_row][player_col] = crumb;
        }
        cpt++;
        ennemies = stepOutput.ennemy;
        prev_act = act;
        prev_pos = new_state;
        // show_matrix(qfunction, rows * cols - 1, nbr_actions);
    }
    printf("Le compteur : %d\n", cpt);
    return 1;
}
