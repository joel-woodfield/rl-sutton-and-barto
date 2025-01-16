//
// Created by Joel Woodfield on 16/01/2025
//

#include <stdlib.h>
#include <stdio.h>

#include "q.h"

static int random_action(Mdp* mdp) {
    float u = (float)rand() / RAND_MAX;
    int action = u * mdp->num_actions;
    return action;
}

static float optimal_value(Mdp* mdp, float** value, int state) {
    float max_value = value[state][0];
    for (int action = 1; action < mdp->num_actions; ++action) {
        if (value[state][action] > max_value) {
            max_value = value[state][action];
        }
    }
    return max_value;
}

static int epsilon_greedy(Mdp* mdp, float** value, float epsilon, int state) {
    float u = (float)rand() / RAND_MAX;
    if (u < epsilon) {
        return random_action(mdp);
    }

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

void train_q(Mdp* mdp, float** value, float gamma, float alpha, 
             float epsilon, int num_episodes) {
    for (int state = 0; state < mdp->num_states; ++state) {
        for (int action = 0; action < mdp->num_actions; ++action) {
            value[state][action] = 0;
        }
    }


    for (int episode = 0; episode < num_episodes; ++episode) {
        int state = mdp->reset();

        while (state != mdp->terminal_state) {
            int action = epsilon_greedy(mdp, value, epsilon, state);
            StateRewardPair next = mdp->step(state, action);
            float optimal_next_value = optimal_value(mdp, value, next.state);
            float td_error = next.reward + gamma * optimal_next_value - value[state][action];
            value[state][action] += alpha * td_error;

            state = next.state;
        }

    }
}