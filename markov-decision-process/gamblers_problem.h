//
// Created by Joel Woodfield on 9/12/2024.
//

#ifndef GAMBLERS_PROBLEM_H
#define GAMBLERS_PROBLEM_H

#include "mdp.h"
#include "bool.h"

#define GOAL_CAPITAL 100
#define HEAD_PROBABILITY 0.5
#define NUM_REWARDS 2

void init_gamblers_problem(Mdp* mdp);
float transition_gamblers_problem(Mdp* mdp, MdpTuple tuple);
bool is_done_gamblers_problem(Mdp* mdp, int state);
void action_set_gamblers_problem(Mdp* mdp, int current_state, int* valid_actions, int* num_valid_actions);
void delete_gamblers_problem(Mdp* mdp);

#endif //GAMBLERS_PROBLEM_H
