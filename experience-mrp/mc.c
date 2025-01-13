//
// Created by Joel Woodfield on 09/01/2025
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "mc.h"

void train_mc(Mrp* mrp, float* value, float gamma, float alpha, int num_episodes) {
    for (int i = 0; i != mrp->num_states; ++i) {
        value[i] = 0;
    }

    bool avg_step_size = alpha < 0;
    int* state_counts;
    if (avg_step_size) {
        state_counts = calloc(mrp->num_states, sizeof(int));
    }
        

    for (int e = 0; e < num_episodes; ++e) {
        int initial_state = mrp->reset();
        // dynamically growing array
        int episode_size = 1000;
        StateRewardPair* episode = malloc(episode_size * sizeof(StateRewardPair));
        
        // collect episode
        int step = 0;
        for (int state = initial_state; state != mrp->terminal_state; ) {
            StateRewardPair next = mrp->step(state);
            episode[step++] = next;
            state = next.state;
    
            if (step >= episode_size) {
                episode_size *= 2;
                episode = realloc(episode, episode_size * sizeof(StateRewardPair));
            }
        }

        // update value
        float ret = 0;
        for (int t = step - 1; t >= 0; --t) {
            ret = ret * gamma + episode[t + 1].reward;

            int state;
            if (t == 0) {
                state = initial_state;
            } else {
                state = episode[t].state;
            }
                
            if (avg_step_size) {
                ++state_counts[mrp->s2i(state)];
                alpha = 1 / (float)state_counts[mrp->s2i(state)];
            }
            
            float error = ret - value[mrp->s2i(state)];
            value[mrp->s2i(state)] = value[mrp->s2i(state)] + alpha * error;
        }
            
        free(episode);
    }

    if (avg_step_size) {
        free(state_counts);
    }
}
            
    
    
