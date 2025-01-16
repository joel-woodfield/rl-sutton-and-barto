#include <stdlib.h>
#include <stdio.h>

#include "cliff_walking.h"
#include "q.h"
#include "sarsa.h"
#include "expected_sarsa.h"


static int optimal_action(Mdp* mdp, float** value, int state) {
    int best_action = 0;
    float max_value = value[state][best_action];
    for (int action = 1; action < mdp->num_actions; ++action) {
        if (value[state][action] > max_value) {
            best_action = action;
            max_value = value[state][action];
        }
    }
    return best_action;
}

static float evaluate(Mdp* mdp, float** value, float gamma, int num_episodes) {
    float total_reward = 0;
    for (int episode = 0; episode < num_episodes; ++episode) {
        float episode_reward = 0;
        int state = mdp->reset();
        while (state != mdp->terminal_state) {
            int action = optimal_action(mdp, value, state);
            StateRewardPair next = mdp->step(state, action);
            episode_reward += next.reward;
            state = next.state;
        }
        total_reward += episode_reward;
    }
    return total_reward / num_episodes;
}

static void train_evaluate(void (*train)(Mdp*, float**, float, float, float, int)) {
    float gamma = 1;
    float alpha = 0.01;
    float epsilon = 0.1;
    int num_episodes = 1000000;
    int num_eval_episodes = 1000;
    Mdp mdp;
    init_cliff_walking(&mdp);

    float** value = malloc(mdp.num_states * sizeof(float*));
    for (int state = 0; state < mdp.num_states; ++state) {
        value[state] = malloc(mdp.num_actions * sizeof(float));
    }

    train(&mdp, value, gamma, alpha, epsilon, num_episodes);
    float avg_reward = evaluate(&mdp, value, gamma, num_eval_episodes);
    printf("Average reward: %f\n", avg_reward);
    print_optimal_actions_cliff_walking(&mdp, value);

    for (int state = 0; state < mdp.num_states; ++state) {
        free(value[state]);
    }
    free(value);
}


int main() {
    printf("Q-learning\n");
    train_evaluate(train_q);
    printf("\n");

    printf("SARSA\n");
    train_evaluate(train_sarsa);
    printf("\n");

    printf("Expected SARSA\n");
    train_evaluate(train_expected_sarsa);
}