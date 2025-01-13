//
// Created by Joel Woodfield on 09/01/2025
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "mrp.h"
#include "random_walk.h"

static StateRewardPair sample(StateRewardPair* pairs, float* cdf, int num_pairs) {
    float u = (float)rand() / RAND_MAX;
    for (int i = 0; i < num_pairs; ++i) {
        if (cdf[i] >= u) {
            return pairs[i];
        }
    }
    fprintf(stderr, "cdf not normalized in sample");
    exit(99);
}

void init_random_walk(Mrp* mrp) {
    mrp->num_states = NUM_STATES;
    mrp->terminal_state = TERMINAL_STATE;
    mrp->reset = reset_random_walk;
    mrp->step = step_random_walk;
    mrp->s2i = s2i_random_walk;
}

int reset_random_walk() {
    return INITIAL_STATE;
}

StateRewardPair step_random_walk(int current_state) {
    // consistent for all next pairs
    int num_next_pairs = 2;
    float cdf[] = {LEFT_PROB, 1};
    StateRewardPair pairs[2];

    // fill in pairs
    if (current_state == LEFT_EDGE) {
        pairs[0].state = TERMINAL_STATE;
        pairs[0].reward = 0;
        pairs[1].state = LEFT_EDGE + 1;
        pairs[1].reward = 0;
    } else if (current_state == RIGHT_EDGE) {
        pairs[0].state = RIGHT_EDGE - 1;
        pairs[0].reward = 0;
        pairs[1].state = TERMINAL_STATE;
        pairs[1].reward = 1;
    } else {
        pairs[0].state = current_state - 1;
        pairs[0].reward = 0;
        pairs[1].state = current_state + 1;
        pairs[1].reward = 0;
    }

    return sample(pairs, cdf, num_next_pairs);
}

int s2i_random_walk(int state) {
    return state + (-LEFT_EDGE);
}
