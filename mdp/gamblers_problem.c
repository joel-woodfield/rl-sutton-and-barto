//
// Created by Joel Woodfield on 9/12/2024.
//

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "gamblers_problem.h"

static int _transition_matrix_index(MdpTuple tuple) {
    static int dim3_step_size = NUM_REWARDS * NUM_STATES * NUM_ACTIONS;
    static int dim2_step_size = NUM_STATES * NUM_ACTIONS;
    static int dim1_step_size = NUM_ACTIONS;

    return tuple.next_state * dim3_step_size + tuple.reward * dim2_step_size
        + tuple.current_state * dim1_step_size + tuple.action;
}

static float _get_transition_matrix(float* transition_matrix, MdpTuple tuple) {
    int index = _transition_matrix_index(tuple);
    return transition_matrix[index];
}

static void _set_transition_matrix(float* transition_matrix, float prob, MdpTuple tuple) {
    int index = _transition_matrix_index(tuple);
    transition_matrix[index] = prob;
}

static float* _init_transition_matrix() {
    // p(s',r|s,a) matrix
    static int matrix_size = NUM_STATES * NUM_REWARDS * NUM_STATES * NUM_ACTIONS;
    // initialize all probabilities to 0
    float* matrix = calloc(matrix_size, sizeof(float));
    if (matrix == NULL) {
        printf("Failed to allocate memory for transition matrix\n");
    }

    // reaching terminal state
    MdpTuple final_transition;
    final_transition.reward = 0;
    final_transition.next_state = TERMINAL_STATE;
    final_transition.action = 0;

    final_transition.current_state = 0;
    _set_transition_matrix(matrix, 1, final_transition);

    for (int final_capital = GOAL_CAPITAL; final_capital < GOAL_CAPITAL + (GOAL_CAPITAL - 1); ++final_capital) {
        final_transition.current_state = final_capital;
        _set_transition_matrix(matrix, 1, final_transition);
    }

    // filling in non-zero probability transitions
    for (int current_state = 1; current_state < GOAL_CAPITAL; ++current_state) {
        // get all possible actions from current state
        int max_action = current_state;
        if (GOAL_CAPITAL - current_state < current_state) {
            max_action = GOAL_CAPITAL - current_state;
        }

        for (int action = 0; action <= max_action; ++action) {
            // true for all next states
            MdpTuple transition;
            transition.current_state = current_state;
            transition.action = action;

            // win coin flip
            transition.next_state = current_state + action;
            transition.reward = transition.next_state >= GOAL_CAPITAL ? 1 : 0;
            _set_transition_matrix(matrix, HEAD_PROBABILITY, transition);

            // lose coin flip
            transition.next_state = current_state - action;
            transition.reward = 0;
            _set_transition_matrix(matrix, 1 - HEAD_PROBABILITY, transition);
        }

    }
    return matrix;
}

void init_gamblers_problem(Mdp* mdp, int* init_state) {
    mdp->num_states = NUM_STATES;
    mdp->num_actions = NUM_ACTIONS;
    mdp->num_rewards = NUM_REWARDS;
    mdp->transition_matrix = _init_transition_matrix();
    mdp->terminal_state = TERMINAL_STATE;
    *init_state = START_CAPITAL;
}

void action_set_gamblers_problem(Mdp* mdp, int current_state, int** valid_actions, int* num_valid_actions) {
    int capital = current_state;
    int max_stake = capital;
    if (GOAL_CAPITAL - capital < capital) {
        max_stake = GOAL_CAPITAL - capital;
    }

    *num_valid_actions = max_stake + 1;  // 0 -> max_stake (inclusive)
    *valid_actions = malloc(*num_valid_actions * sizeof(int));
    for (int i = 0; i <= max_stake; ++i) {
        (*valid_actions)[i] = i;
    }
}

float transition_gamblers_problem(Mdp* mdp, MdpTuple tuple) {
    return _get_transition_matrix(mdp->transition_matrix, tuple);
}

bool is_done_gamblers_problem(Mdp* mdp, int current_state) {
    return current_state == mdp->terminal_state;
}

void delete_gamblers_problem(Mdp* mdp) {
    free(mdp->transition_matrix);
}
