#include <stdio.h>
#include "qlearning.h"
#include "functions.h"
#include "mazeEnv.h"

int policy_greedy(int state)
{
    return maxlist(qfunction[state], number_actions, true);
}

int policy_epsgreedy(int state, float epsi)
{
    int actio = 0;
    float alea = ((float)rand()) / RAND_MAX;
    if (alea < epsi)
    {
        actio = env_action_sample();
    }
    else
    {
        actio = maxlist(qfunction[state], number_actions, true);
    }
    return actio;
}