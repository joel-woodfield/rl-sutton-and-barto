//
// Created by Joel Woodfield on 09/01/2025.
//

#ifndef MRP_H
#define MRP_H

typedef struct {
    int state;
    int reward;
} StateRewardPair;

typedef struct {
    int num_states;
	int terminal_state;
    int (*reset)();
    StateRewardPair (*step)(int state);
    int (*s2i)(int state);
} Mrp;

#endif //MRP_H
