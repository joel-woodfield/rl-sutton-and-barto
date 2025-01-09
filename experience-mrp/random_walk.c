//
// Created by Joel Woodfield on 09/01/2025
//

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "mrp.h"
#include "random_walk.h"

static float* access_matrix(float* matrix, int dim1, int dim2, int dim3) {
    return &matrix[dim1 * NUM_REWARDS * NUM_STATES + dim2 * NUM_STATES + dim3];
}

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

int init_random_walk(Mrp* mrp) {
    mrp->num_states = NUM_STATES;
    mrp->num_rewards = NUM_REWARDS;
    mrp->terminal_state = TERMINAL_STATE;

    // the matrix will not be stored - sampling is taken care of by step_ranodm_walk().
    mrp->transition_matrix = NULL;

    return INITIAL_STATE;
}

StateRewardPair step_random_walk(Mrp* mrp, int current_state) {
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

bool is_done_random_walk(Mrp* mrp, int state) {
    return state == mrp->terminal_state;
}

void delete_random_walk(Mrp* mrp) {
    // nothing to do
}

int s2i_random_walk(int state) {
    return state + (-LEFT_EDGE);
}
