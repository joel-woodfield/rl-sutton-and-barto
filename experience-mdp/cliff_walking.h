//
// Created by Joel Woodfield on 13/01/2025
//

#ifndef CLIFF_WALKING_H
#define CLIFF_WALKING_H

#include "mdp.h"

#define GRID_WIDTH 12
#define GRID_HEIGHT 4
#define NUM_STATES GRID_WIDTH * GRID_HEIGHT + 1  // +1 for terminal state
#define TERMINAL_STATE NUM_STATES - 1 
#define INITIAL_STATE 0
#define GOAL_STATE GRID_WIDTH - 1

#define UP_EFFECT GRID_WIDTH
#define RIGHT_EFFECT 1
#define DOWN_EFFECT -GRID_WIDTH
#define LEFT_EFFECT -1
#define NUM_ACTIONS 4

#define FALL_REWARD -100
#define DEFAULT_REWARD -1

void init_cliff_walking(Mdp* mdp);

int reset_cliff_walking();
StateRewardPair step_cliff_walking(int state, int action);
int s2i_cliff_walking(int state);

void print_optimal_actions_cliff_walking(Mdp* mdp, float** value);


#endif //CLIFF_WALKING_H