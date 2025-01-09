//
// Created by Joel Woodfield on 09/01/2025.
//

#ifndef MRP_H
#define MRP_H

typedef struct {
	int num_states;
    int num_rewards;
	float* transition_matrix;
	int terminal_state;
} Mrp;

typedef struct {
    int state;
    int reward;
} StateRewardPair;

typedef struct {
    int next_state;
    int reward;
    int current_state;
} MrpTuple;

#endif //MRP_H
