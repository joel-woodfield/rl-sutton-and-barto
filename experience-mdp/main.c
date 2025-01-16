#include <stdlib.h>
#include <stdio.h>

#include "cliff_walking.h"
#include "q.h"
#include "sarsa.h"

int main() {
    float gamma = 1;
    float alpha = 0.01;
    float epsilon = 0.1;
    int num_episodes = 1000000;
    Mdp mdp;
    init_cliff_walking(&mdp);

    float** value = malloc(mdp.num_states * sizeof(float*));
    for (int state = 0; state < mdp.num_states; ++state) {
        value[state] = malloc(mdp.num_actions * sizeof(float));
    }

    train_q(&mdp, value, gamma, alpha, epsilon, num_episodes);

    for (int y = GRID_HEIGHT - 1; y >= 0; --y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            int state = y * GRID_WIDTH + x;

            int best_action = 0;
            float max_value = value[state][best_action];
            for (int action = 1; action < mdp.num_actions; ++action) {
                if (value[state][action] > max_value) {
                    max_value = value[state][action];
                    best_action = action;
                }
            }

            char c;
            switch (best_action) {
                case 0:
                    c = 'U';
                    break;
                case 1:
                    c = 'R';
                    break;
                case 2:
                    c = 'D';
                    break;
                case 3:
                    c = 'L';
                    break;
            }
            // wall
            if (state > 0 && state < GRID_WIDTH) {
                c = 'x';
            }
            // goal
            if (state == GOAL_STATE) {
                c = 'o';
            }

            printf("%c ", c);
            // printf("%f ", value[state][3]);
        }
        printf("\n");
    }

    for (int state = 0; state < mdp.num_states; ++state) {
        free(value[state]);
    }
    free(value);
}