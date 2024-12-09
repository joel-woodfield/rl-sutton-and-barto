//
// Created by Joel Woodfield on 9/12/2024.
//

#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "gamblers_problem.h"

static int _transition_matrix_index(float* transition_matrix, MdpTuple tuple) {
    static int dim3_step_size = NUM_REWARDS * GOAL_CAPITAL * GOAL_CAPITAL;
    static int dim2_step_size = GOAL_CAPITAL * GOAL_CAPITAL;
    static int dim1_step_size = GOAL_CAPITAL;

    return tuple.next_state * dim3_step_size + tuple.reward * dim2_step_size
        + tuple.current_state * dim1_step_size + tuple.action;
}

static float _get_transition_matrix(float* transition_matrix, MdpTuple tuple) {
    int index = _transition_matrix_index(transition_matrix, tuple);
    return transition_matrix[index];
}

static void _set_transition_matrix(float* transition_matrix, float prob, MdpTuple tuple) {
    int index = _transition_matrix_index(transition_matrix, tuple);
    transition_matrix[index] = prob;
}

static float* _init_transition_matrix(int num_states, int num_actions) {
    // p(s',r|s,a) ==> Matrix of NUM_STATES x NUM_REWARDS x NUM_STATES x NUM_ACTIONS
    size_t matrix_size = num_states * NUM_REWARDS * num_states * num_actions;
    // initialize all probabilities to 0
    float* matrix = calloc(matrix_size, sizeof(float));

    for (int current_state = 0; current_state < num_states; ++current_state) {
        // get all possible actions from current state
        int capital = current_state;
        int max_stake = capital;
        if (GOAL_CAPITAL - capital < capital) {
            max_stake = GOAL_CAPITAL - capital;
        }

        for (int stake = 0; stake <= max_stake; ++stake) {
            int reward = capital < GOAL_CAPITAL ? 0 : 1;

            // two possible outcomes - win and lose coin flip

            MdpTuple win_transition;
            win_transition.current_state = current_state;
            win_transition.action = stake;
            win_transition.reward = reward;
            win_transition.next_state = capital + stake;
            float win_prob = HEAD_PROBABILITY;
            _set_transition_matrix(matrix, win_prob, win_transition);

            MdpTuple lose_transition;
            lose_transition.current_state = current_state;
            lose_transition.action = stake;
            lose_transition.reward = reward;
            lose_transition.next_state = capital - stake;
            float lose_prob = 1 - HEAD_PROBABILITY;
            _set_transition_matrix(matrix, lose_prob, lose_transition);
        }
    }
}

void init_gamblers_problem(Mdp* mdp) {
    mdp->num_states = GOAL_CAPITAL;
    mdp->num_actions = GOAL_CAPITAL;  // max_s(A(s))
    mdp->transition_matrix = _init_transition_matrix(mdp->num_states, mdp->num_actions);
    mdp->terminal_state = 0;
}

void action_set_gamblers_problem(Mdp* mdp, int current_state, int** valid_actions, int* num_valid_actions) {
    int capital = current_state;
    int max_stake = capital;
    if (GOAL_CAPITAL - capital < capital) {
        max_stake = GOAL_CAPITAL - capital;
    }

    *num_valid_actions = max_stake;
    *valid_actions = malloc(*num_valid_actions * sizeof(int));
    for (int i = 0; i < max_stake; ++i) {
        valid_actions[i] = i;
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
    free(mdp);
}
