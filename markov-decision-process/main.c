//
// Created by joel on 12/13/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "mdp.h"
#include "gamblers_problem.h"

#define NUM_ITERATIONS 1

int main() {
    Mdp mdp;
    int state;
    init_gamblers_problem(&mdp, &state);

    int* valid_actions;
    int num_actions;
    for (int i = 0; i < NUM_ITERATIONS; ++i) {
        action_set_gamblers_problem(&mdp, state, &valid_actions, &num_actions);
        const int random_idx = rand() % num_actions;
        const int action = valid_actions[random_idx];
        MdpTuple transition;
        transition.action = action;
        transition.current_state = state;
        transition.next_state = state;
        transition.reward = 0;
        printf("Prob: %f\n", transition_gamblers_problem(&mdp, transition));
        transition.next_state = state + action;
        printf("Prob: %f\n", transition_gamblers_problem(&mdp, transition));

        free(valid_actions);
    }
    delete_gamblers_problem(&mdp);
}
