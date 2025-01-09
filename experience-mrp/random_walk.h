//
// Created by Joel Woodfield on 09/01/2025
//

#ifndef RANDOM_WALK_H
#define RANDOM_WALK_H

#include <stdbool.h>

#include "mrp.h"

#define NUM_REWARDS 2

#define RIGHT_EDGE 2
#define LEFT_EDGE -RIGHT_EDGE
#define INITIAL_STATE 0
#define TERMINAL_STATE RIGHT_EDGE + 1
#define NUM_STATES RIGHT_EDGE * 2 + 2 // one for state 0, one for terminal

#define LEFT_PROB 0.5
#define RIGHT_PROB 1 - LEFT_PROB

/**
 * Initializes the mrp object and returns the initial state.
 */
int init_random_walk(Mrp* mrp);

/**
 * Returns the next state and reward based on the given mrp and state.
 */
StateRewardPair step_random_walk(Mrp* mrp, int current_state);

/**
 * Returns whether the given state is a terminal state.
 */
bool is_done_random_ralk(Mrp* mrp, int state);

void delete_random_walk(Mrp* mrp);

int s2i_random_walk(int state);

#endif //RANDOM_WALK_H
