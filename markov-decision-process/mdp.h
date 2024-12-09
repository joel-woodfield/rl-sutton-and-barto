//
// Created by Joel Woodfield on 9/12/2024.
//

#ifndef MDP_H
#define MDP_H

typedef struct {
	int num_states;
	int num_actions;
	float* transition_matrix;
	int terminal_state;
} Mdp;

typedef struct {
    int state;
    int reward;
} StateRewardPair;

typedef struct {
    int next_state;
    int reward;
    int current_state;
    int action;
} MdpTuple

#endif //MDP_H
