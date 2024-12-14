//
// Created by joel on 12/13/24.
//

#ifndef POLICY_ITERATION_H
#define POLICY_ITERATION_H

#include "mdp.h"

typedef struct {
    float* value;
    int* policy;
    int num_states;
    float value_threshold;
    float gamma;
} PolicyIterationAgent;

void init_policy_iteration(PolicyIterationAgent* agent, Mdp* mdp,
                           float value_threshold, float gamma);
void solve_mdp(PolicyIterationAgent* agent, int max_iterations, Mdp* mdp,
               float (*transition)(Mdp*, MdpTuple),
               void (*action_set)(Mdp*, int, int**, int*));
void eval_policy(PolicyIterationAgent* agent, Mdp* mdp,
                 float (*transition)(Mdp*, MdpTuple));
bool imp_policy(PolicyIterationAgent* agent, Mdp* mdp,
                float (*transition)(Mdp*, MdpTuple), 
                void (*action_set)(Mdp*, int, int**, int*));
void delete_policy_iteration(PolicyIterationAgent* agent);


#endif //POLICY_ITERATION_H
