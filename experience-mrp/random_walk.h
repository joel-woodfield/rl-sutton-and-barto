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
 * Initializes the mrp object
 */
void init_random_walk(Mrp* mrp);

/**
 * Returns an initial state from the initial state distribution.
 */
int reset_random_walk();

/**
 * Returns the next state and reward based on the given state.
 */
StateRewardPair step_random_walk(int current_state);

/**
 * Returns a unique positive index corresponding to the given state.
 * Useful for array indexing.
 */
int s2i_random_walk(int state);

#endif //RANDOM_WALK_H
