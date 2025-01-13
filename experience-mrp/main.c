#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "random_walk.h"
#include "td0.h"
#include "mc.h"

int main() {
    float gamma = 1;
    float alpha = 0.01;
    int num_episodes = 10000;
    Mrp mrp;
    init_random_walk(&mrp);

    // true
    printf("True\n");
    float* true_value = malloc(mrp.num_states * sizeof(float));
    for (int state = LEFT_EDGE; state <= RIGHT_EDGE; ++state) {
        float value = (float)(s2i_random_walk(state) + 1) / ((RIGHT_EDGE + 1) * 2);
        true_value[s2i_random_walk(state)] = value;
        printf("V(%d) = %f\n", state, value);
    }
    printf("\n");

    // td0
    printf("TD0\n");
    float sse = 0;
    float* value = malloc(mrp.num_states * sizeof(float));
    train_td0(&mrp, value, gamma, alpha, num_episodes);

    for (int state = LEFT_EDGE; state <= RIGHT_EDGE; ++state) {
        sse += powf(value[s2i_random_walk(state)] - true_value[s2i_random_walk(state)], 2);
        printf("V(%d) = %f\n", state, value[s2i_random_walk(state)]);
    }
    free(value);
    printf("MSE = %f\n", sqrtf(sse));
    printf("\n");

    // td0 average step size
    printf("TD0 average step size\n");
    sse = 0;
    value = malloc(mrp.num_states * sizeof(float));
    train_td0(&mrp, value, gamma, -1, num_episodes);

    for (int state = LEFT_EDGE; state <= RIGHT_EDGE; ++state) {
        sse += powf(value[s2i_random_walk(state)] - true_value[s2i_random_walk(state)], 2);
        printf("V(%d) = %f\n", state, value[s2i_random_walk(state)]);
    }
    free(value);
    printf("MSE = %f\n", sqrtf(sse));
    printf("\n");

    // mc
    printf("MC\n");
    sse = 0;
    value = malloc(mrp.num_states * sizeof(float));
    train_mc(&mrp, value, gamma, alpha, num_episodes);

    for (int state = LEFT_EDGE; state <= RIGHT_EDGE; ++state) {
        sse += powf(value[s2i_random_walk(state)] - true_value[s2i_random_walk(state)], 2);
        printf("V(%d) = %f\n", state, value[s2i_random_walk(state)]);
    }
    free(value);
    printf("MSE = %f\n", sqrtf(sse));
    printf("\n");

    // mc avg step size
    printf("MC average step size\n");
    sse = 0;
    value = malloc(mrp.num_states * sizeof(float));
    train_mc(&mrp, value, gamma, -1, num_episodes);

    for (int state = LEFT_EDGE; state <= RIGHT_EDGE; ++state) {
        sse += powf(value[s2i_random_walk(state)] - true_value[s2i_random_walk(state)], 2);
        printf("V(%d) = %f\n", state, value[s2i_random_walk(state)]);
    }
    free(value);
    printf("MSE = %f\n", sqrtf(sse));


    free(true_value);

}
    
