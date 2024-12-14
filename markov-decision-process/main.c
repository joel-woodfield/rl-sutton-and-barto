//
// Created by joel on 12/13/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "mdp.h"
#include "gamblers_problem.h"
#include "policy_iteration.h"

#define MAX_ITERATIONS 1000
#define OUTPUT_FILE_PATH "../outputs/gambler.csv"

int main() {
    Mdp mdp;
    int state;
    init_gamblers_problem(&mdp, &state);

    PolicyIterationAgent agent;
    init_policy_iteration(&agent, &mdp, 1e-4f, 0.99f);
    solve_mdp(&agent, MAX_ITERATIONS, &mdp, transition_gamblers_problem,
              action_set_gamblers_problem);

    save_policy_iteration(&agent, OUTPUT_FILE_PATH);
    delete_gamblers_problem(&mdp);
    delete_policy_iteration(&agent);
}
