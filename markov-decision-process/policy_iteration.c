//
// Created by joel on 12/14/24.
//
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "policy_iteration.h"
#include "gamblers_problem.h"

void init_policy_iteration(PolicyIterationAgent* agent, Mdp* mdp, float value_threshold, float gamma) {
    agent->num_states = mdp->num_states;
    agent->value = calloc(mdp->num_states, sizeof(float));
    agent->policy = calloc(mdp->num_states, sizeof(float));
    agent->value_threshold = value_threshold;
    agent->gamma = gamma;
}

void solve_mdp(PolicyIterationAgent* agent, int max_iterations, Mdp* mdp,
               float (*transition)(Mdp*, MdpTuple),
               void (*action_set)(Mdp*, int, int**, int*)) {
    bool converged = false;
    int iterations = max_iterations;

    for (int i = 0; i < max_iterations; ++i) {
        printf("\rIter: %d", i);
        fflush(stdout);

        eval_policy(agent, mdp, transition);
        converged = imp_policy(agent, mdp, transition, action_set);
        if (converged) {
            iterations = i;
            break;
        }
    }
    printf("\r\n");
    if (converged) {
        printf("Policy converged after %d iterations\n", iterations);
    } else {
        printf("Policy did not converge after %d iterations\n", iterations);
    }
}

void eval_policy(PolicyIterationAgent* agent, Mdp* mdp,
                 float (*transition)(Mdp*, MdpTuple)) {
    while (true) {
        float max_error = 0;

        for (int state = 0; state < mdp->num_states; ++state) {
            if (state == mdp->terminal_state) {
                continue;
            }
            float old_value = agent->value[state];
            float new_value = 0;
            for (int next_state = 0; next_state < mdp->num_states;
                 ++next_state) {
                for (int reward = 0; reward < mdp->num_rewards; ++reward) {
                    MdpTuple tuple;
                    tuple.current_state = state;
                    tuple.action = agent->policy[state];
                    tuple.next_state = next_state;
                    tuple.reward = reward;

                    new_value += transition(mdp, tuple)
                        * (reward + agent->gamma 
                        * agent->value[next_state]);
                }
            }
            agent->value[state] = new_value;
            float error = fabsf(new_value - old_value);
            if (error > max_error) {
                max_error = error;
            }
        }

        if (max_error < agent->value_threshold) {
            break;
        }
    }
}

bool imp_policy(PolicyIterationAgent* agent, Mdp* mdp,
                float (*transition)(Mdp*, MdpTuple), 
                void (*action_set)(Mdp*, int, int**, int*)) {
    bool policy_converged = true;
    for (int state = 0; state < agent->num_states; ++state) {
        int old_action = agent->policy[state];

        // find action that maximises expected value
        int next_action = old_action;  // represents uninitialized action
        float max_value = -INFINITY;

        int* valid_actions;
        int num_valid_actions;
        action_set(mdp, state, &valid_actions, &num_valid_actions);

        for (int i = 0; i < num_valid_actions; ++i) {
            int action = valid_actions[i];
            float value = 0;
            for (int next_state = 0; next_state < mdp->num_states;
                 ++next_state) {
                for (int reward = 0; reward < mdp->num_rewards;
                     ++reward) {
                    MdpTuple tuple;
                    tuple.current_state = state;
                    tuple.action = action;
                    tuple.next_state = next_state;
                    tuple.reward = reward;

                    value += transition(mdp, tuple)
                        * ((float)reward + agent->gamma
                        * agent->value[next_state]);
                     }
                 }
            if (value > max_value) {
                next_action = action;
                max_value = value;
            }
        }
        agent->policy[state] = next_action;
        if (old_action != next_action) {
            policy_converged = false;
        }

        free(valid_actions);
    }

    return policy_converged;
}

void delete_policy_iteration(PolicyIterationAgent* agent) {
    free(agent->value);
    free(agent->policy);
}
