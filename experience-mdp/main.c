#include <stdlib.h>
#include <stdio.h>

#include "cliff_walking.h"
#include "sarsa.h"

int main() {
    float gamma = 1;
    float alpha = 0.01;
    float epsilon = 0.1;
    int num_episodes = 10000;
    Mdp mdp;
    init_cliff_walking(&mdp);

    float** value = malloc(mdp.num_states * sizeof(float*));
    for (int state = 0; state < mdp.num_states; ++state) {
        value[state] = malloc(mdp.num_actions * sizeof(float));
    }

    train_sarsa(&mdp, value, gamma, alpha, epsilon, num_episodes);

    for (int x = 0; x < GRID_WIDTH; ++x) {
        for (int y = GRID_HEIGHT - 1; y >= 0; --y) {
            int state = y * GRID_WIDTH + x;

            int best_action = 0;
            float max_value = value[state][best_action];
            for (int action = 0; action < mdp.num_actions; ++action) {
                if (value[state][action] > max_value) {
                    max_value = value[state][action];
                    best_action = action;
                }
            }

            char c = '?';
            switch (best_action) {
                case 0:
                    c = 'U';
                case 1:
                    c = 'R';
                case 2:
                    c = 'D';
                case 3:
                    c = 'L';
            }
            printf("%c ", c);
        }
        printf("\n");
    }

    for (int state = 0; state < mdp.num_states; ++state) {
        free(value[state]);
    }
    free(value);
}