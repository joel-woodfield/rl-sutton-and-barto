//
// Created by Joel Woodfield on 13/01/2025
//
#include <stdlib.h>
#include <stdio.h>

#include "sarsa.h"

static int random_action(Mdp* mdp) {
    float u = (float)rand() / RAND_MAX;
    int action = u * mdp->num_actions;
    return action;
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

void train_sarsa(Mdp* mdp, float** value, float gamma, float alpha, 
                 float epsilon, int num_episodes) {
    for (int state = 0; state < mdp->num_states; ++state) {
        for (int action = 0; action < mdp->num_actions; ++action)
        value[state][action] = 0;
    }

    for (int episode = 0; episode < num_episodes; ++episode) {
        int state = mdp->reset();
        int action = epsilon_greedy(mdp, value, epsilon, state);

        while (state != mdp->terminal_state) {
            StateRewardPair next = mdp->step(state, action);
            int next_action = epsilon_greedy(mdp, value, epsilon, next.state);
            float td_error = next.reward + gamma * value[next.state][next_action] - value[state][action];
            value[state][action] += alpha * td_error;

            state = next.state;
            action = next_action;
        }
    }
}