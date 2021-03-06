#include <stdio.h>
#include "qlearning.h"
#include "functions.h"
#include "mazeEnv.h"
#include "policies.h"

int policy_greedy(int state, double *list)
{
    return maxlist(list, number_actions, true);
}

int policy_epsgreedy(int state, float epsi, double *list)
{
    int actio = 0;
    float alea = ((float)rand()) / RAND_MAX;
    if (alea < epsi)
    {
        actio = env_action_sample();
    }
    else
    {
        actio = maxlist(list, number_actions, true);
    }
    return actio;
}