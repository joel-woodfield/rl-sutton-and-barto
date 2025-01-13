//
// Created by Joel Woodfield on 09/01/2025
//
#include <stdbool.h>
#include <stdlib.h>

#include "td0.h"

void train_td0(Mrp* mrp, float* value, float gamma, float alpha, int num_episodes) {
    for (int i = 0; i != mrp->num_states; ++i) {
        value[i] = 0;
    }

    bool avg_step_size = alpha < 0;
    int* state_counts;
    if (avg_step_size) {
        state_counts = calloc(mrp->num_states, sizeof(int));
    }

    for (int e = 0; e < num_episodes; ++e) {
        int state = mrp->reset();
        while (state != mrp->terminal_state) {
            StateRewardPair next = mrp->step(state);

            float td_error = gamma * value[mrp->s2i(next.state)] + next.reward 
                    - value[mrp->s2i(state)];

            if (avg_step_size) {
                ++state_counts[mrp->s2i(state)];
                alpha = 1 / (float)state_counts[mrp->s2i(state)];
            }

            value[mrp->s2i(state)] = value[mrp->s2i(state)] + alpha * td_error;
            state = next.state;
        }
    }

    if (avg_step_size) {
        free(state_counts);
    }
}
            
    
    
