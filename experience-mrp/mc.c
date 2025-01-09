//
// Created by Joel Woodfield on 09/01/2025
//

#include <stdlib.h>
#include <stdio.h>

#include "mc.h"

void train_mc(Mrp* mrp, int (*init_mrp)(Mrp*), StateRewardPair (*step_mrp)(Mrp*, int),
           int (*s2i_mrp)(int), float* value, float gamma, float alpha, int num_episodes) {
    for (int i = 0; i != mrp->num_states; ++i) {
        value[i] = 0;
    }

    for (int e = 0; e < num_episodes; ++e) {
        int initial_state = init_mrp(mrp);
        // dynamically growing array
        int episode_size = 1000;
        StateRewardPair* episode = malloc(episode_size * sizeof(StateRewardPair));
        
        // collect episode
        int step = 0;
        for (int state = initial_state; state != mrp->terminal_state; ) {
            StateRewardPair next = step_mrp(mrp, state);
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
                
            float error = ret - value[s2i_mrp(state)];
            value[s2i_mrp(state)] = value[s2i_mrp(state)] + alpha * error;
        }
            
        free(episode);
        
    }
}
            
    
    
