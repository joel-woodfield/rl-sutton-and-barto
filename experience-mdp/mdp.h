//
// Created by Joel Woodfield on 13/01/2025
//

#ifndef MDP_H
#define MDP_H

typedef struct {
    int state;
    int reward;
} StateRewardPair;

typedef struct {
    int num_states;
    int terminal_state;
    int num_actions;
    int (*reset)();
    StateRewardPair(*step)(int state, int action);
    int (*s2i)(int state);
} Mdp;

#endif //MDP_H