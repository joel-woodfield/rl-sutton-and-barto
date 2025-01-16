//
// Created by Joel Woodfield on 13/01/2025
//
#include <stdio.h>
#include <stdbool.h>

#include "cliff_walking.h"

static bool is_wall(int state) {
    return state > 0 && state < GRID_WIDTH - 1;
}

static bool is_goal(int state) {
    return state == GOAL_STATE;
}

void init_cliff_walking(Mdp* mdp) {
    mdp->num_states = NUM_STATES;
    mdp->terminal_state = TERMINAL_STATE;
    mdp->num_actions = NUM_ACTIONS;
    mdp->reset = reset_cliff_walking;
    mdp->step = step_cliff_walking;
    mdp->s2i = s2i_cliff_walking;
}

int reset_cliff_walking() {
    return INITIAL_STATE;
}

StateRewardPair step_cliff_walking(int state, int action) {
    StateRewardPair next;
    int next_state;
    switch (action) {
        case 0:
            next_state = state + UP_EFFECT;
            break;
        case 1:
            next_state = state + RIGHT_EFFECT;
            break;
        case 2:
            next_state = state + DOWN_EFFECT;
            break;
        case 3:
            next_state = state + LEFT_EFFECT;
            break;
    }

    // return same state if out of bounds
    if (next_state < 0 || next_state >= TERMINAL_STATE) {
        return (StateRewardPair){.state = state, .reward = DEFAULT_REWARD};
    }
    if ((next_state / GRID_WIDTH) != (state / GRID_WIDTH) && (next_state % GRID_WIDTH) != (state % GRID_WIDTH)) {
        return (StateRewardPair){.state = state, .reward = DEFAULT_REWARD};
    }

    // fallen off cliff
    if (next_state > 0 && next_state < GRID_WIDTH - 1) {
        return (StateRewardPair){.state = TERMINAL_STATE, .reward = FALL_REWARD};
    }

    // reach goal
    if (next_state == GOAL_STATE) {
        return (StateRewardPair){.state = TERMINAL_STATE, .reward = DEFAULT_REWARD};
    }

    // default case
    return (StateRewardPair){.state = next_state, .reward = DEFAULT_REWARD};
}

int s2i_cliff_walking(int state) {
    // all states are already numbered from 0->NUM_STATES
    return state;
}

void print_optimal_actions_cliff_walking(Mdp* mdp, float** value) {
    for (int y = GRID_HEIGHT - 1; y >= 0; --y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            int state = y * GRID_WIDTH + x;

            int best_action = 0;
            float max_value = value[state][best_action];
            for (int action = 1; action < mdp->num_actions; ++action) {
                if (value[state][action] > max_value) {
                    max_value = value[state][action];
                    best_action = action;
                }
            }

            char c;
            switch (best_action) {
                case 0:
                    c = 'U';
                    break;
                case 1:
                    c = 'R';
                    break;
                case 2:
                    c = 'D';
                    break;
                case 3:
                    c = 'L';
                    break;
            }
            if (is_wall(state)) {
                c = 'x';
            } else if (is_goal(state)) {
                c = 'o';
            }

            printf("%c ", c);
        }
        printf("\n");
    }
}