#include <stdio.h>
#include "agent.h"
#include "utils.h"
#include "environment.h"
#include "policies.h"

int policy_greedy(int state, double *list)
{
    return maxlist(list, nbr_actions, true);
}

action env_action_sample()
{
    return (enum action)(rand() % nbr_actions);
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
        actio = maxlist(list, nbr_actions, true);
    }
    return actio;
}