//
// Created by Joel Woodfield on 09/01/2025
//

#include "td0.h"

void train_td0(Mrp* mrp, int (*init_mrp)(Mrp*), StateRewardPair (*step_mrp)(Mrp*, int),
           int (*s2i_mrp)(int), float* value, float gamma, float alpha, int num_episodes) {
    for (int i = 0; i != mrp->num_states; ++i) {
        value[i] = 0;
    }

    for (int e = 0; e < num_episodes; ++e) {
        int state = init_mrp(mrp);
        while (state != mrp->terminal_state) {
            StateRewardPair next = step_mrp(mrp, state);
            float td_error = gamma * value[s2i_mrp(next.state)] + next.reward 
                    - value[s2i_mrp(state)];
            value[s2i_mrp(state)] = value[s2i_mrp(state)] + alpha * td_error;
            state = next.state;
        }
    }
}
            
    
    
