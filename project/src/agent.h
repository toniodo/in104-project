#ifndef __AGENT_H__
#define __AGENT_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

double **qfunction;
int max_step;
int move;

int make_epoch();

void q_alloc();

void q_initialisation();

#endif