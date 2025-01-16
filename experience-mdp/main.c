#include <stdlib.h>
#include <stdio.h>

#include "cliff_walking.h"
#include "q.h"
#include "sarsa.h"
#include "expected_sarsa.h"


int main() {
    float gamma = 1;
    float alpha = 0.01;
    float epsilon = 0.1;
    int num_episodes = 1000000;
    Mdp mdp;
    init_cliff_walking(&mdp);

    StateRewardPair next = mdp.step(0, 1);

    float** value = malloc(mdp.num_states * sizeof(float*));
    for (int state = 0; state < mdp.num_states; ++state) {
        value[state] = malloc(mdp.num_actions * sizeof(float));
    }

    train_expected_sarsa(&mdp, value, gamma, alpha, epsilon, num_episodes);

    print_optimal_actions_cliff_walking(&mdp, value);

    for (int state = 0; state < mdp.num_states; ++state) {
        free(value[state]);
    }
    free(value);
}