#ifndef POLICIES_H
#define POLICIES_H

#include <stdio.h>
#include <stdlib.h>

int policy_greedy(int state);

int policy_epsgreedy(int state, float epsi);

#endif