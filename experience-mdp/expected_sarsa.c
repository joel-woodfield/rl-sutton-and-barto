//
// Created by Joel Woodfield on 16/01/2025
//
#include <stdlib.h>

#include "expected_sarsa.h"

static int random_action(Mdp* mdp) {
    float u = (float)rand() / RAND_MAX;
    int action = u * mdp->num_actions;
    return action;
}

static int optimal_action(Mdp* mdp, float** value, int state) {
    int best_action = 0;
    float max_value = value[state][best_action];
    for (int action = 1; action < mdp->num_actions; ++action) {
        if (value[state][action] > max_value) {
            best_action = action;
            max_value = value[state][action];
        }
    }
    return best_action;
}

static int epsilon_greedy(Mdp* mdp, float** value, float epsilon, int state) {
    float u = (float)rand() / RAND_MAX;
    if (u < epsilon) {
        return random_action(mdp);
    }

    return optimal_action(mdp, value, state);
}

static float expected_value(Mdp* mdp, float** value, int state, float epsilon) {
    int optimal = optimal_action(mdp, value, state);
    
    float expected_value = 0;
    for (int action = 0; action < mdp->num_actions; ++action) {
        float prob;
        if (action == optimal) {
            prob = 1 - epsilon + epsilon / mdp->num_actions;
        } else {
            prob = epsilon / mdp->num_actions;
        }

        expected_value += prob * value[state][action];
    }
    return expected_value;
}

void train_expected_sarsa(Mdp* mdp, float** value, float gamma, float alpha, 
                          float epsilon, int num_episodes) {
    for (int state = 0; state < mdp->num_states; ++state) {
        for (int action = 0; action < mdp->num_actions; ++action) {
            value[state][action] = 0;
        }
    }

    for (int episode = 0; episode < num_episodes; ++episode) {
        int state = mdp->reset();
        int action = epsilon_greedy(mdp, value, epsilon, state);

        while (state != mdp->terminal_state) {
            StateRewardPair next = mdp->step(state, action);
            int next_action = epsilon_greedy(mdp, value, epsilon, next.state);
            float expected_next_value = expected_value(mdp, value, next.state, epsilon);
            float td_error = next.reward + gamma * expected_next_value - value[state][action];
            value[state][action] += alpha * td_error;

            state = next.state;
            action = next_action;
        }
    }
}