#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct Problem {
    float* values;
    float variance;
    int num_actions;
};

struct Agent {
    float epsilon;
    float* value_estimates;
    int* action_counts;
};

float sample_normal(const float mean, const float stddev) {
    const float u1 = (float)rand() / RAND_MAX;
    const float u2 = (float)rand() / RAND_MAX;

    const float z0 = sqrtf(-2.0f * logf(u1)) * cosf(2.0f * M_PI * u2);
    return z0 * stddev + mean;
}

void init_values(float* values, const int num_actions) {
    for (int i = 0; i != num_actions; ++i) {
        values[i] = sample_normal(0, 1);
    }
}

int get_action(const struct Agent agent, const int num_actions) {
    int action;

    const float u = (float)rand() / RAND_MAX;
    if (u < agent.epsilon) {
        action = rand() % num_actions;
    } else {
        int best_action = 0;
        float max_value_estimate = agent.value_estimates[0];
        for (int i = 1; i != num_actions; ++i) {
            if (agent.value_estimates[i] > max_value_estimate) {
                max_value_estimate = agent.value_estimates[i];
                best_action = i;
            }
        }
        action =  best_action;
    }

    return action;
}

float get_reward(const struct Problem problem, const int action) {
    const float value = problem.values[action];
    const float reward = sample_normal(value, problem.variance);
    return reward;
}

void update_agent(struct Agent agent, int action, float reward) {
    ++agent.action_counts[action];
    const float step_size = 1.0f / agent.action_counts[action];
    const float error = reward - agent.value_estimates[action];
    agent.value_estimates[action] += step_size * error;
}

void run_trial(float* rewards, const struct Problem problem, struct Agent agent, const int num_steps) {
    memset(rewards, 0, num_steps * sizeof(float));
    memset(agent.value_estimates, 0, problem.num_actions * sizeof(float));
    memset(agent.action_counts, 0, problem.num_actions * sizeof(int));

    for (int step = 0; step != num_steps; ++step) {
        int action = get_action(agent, problem.num_actions);
        float reward = get_reward(problem, action);
        rewards[step] = reward;
        update_agent(agent, action, reward);
    }
}

void run_trials(float* rewards, const struct Problem problem, const struct Agent agent, const int num_runs, const int num_steps) {
    for (int run = 0; run != num_runs; ++run) {
        init_values(problem.values, problem.num_actions);
        run_trial(rewards + num_steps * run, problem, agent, num_steps);
    }
}

void save_rewards(const char* filename, const float* rewards, const int num_runs, const int num_steps) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open output file\n");
        exit(2);
    }

    for (int run = 0; run != num_runs; ++run) {
        int step = 0;
        for (; step != num_steps - 1; ++step) {
            fprintf(file, "%f,", rewards[run * num_steps + step]);
        }
        fprintf(file, "%f\n", rewards[run * num_steps + step]);
    }

    fclose(file);
}

int main(int argc, char** argv) {
    if (argc != 7) {
        fprintf(stderr, "Requires 7 arguments\n");
        exit(1);
    }
    const float epsilon = atof(argv[1]);
    const int num_actions = atoi(argv[2]);
    const float variance = atof(argv[3]);
    const int num_steps = atoi(argv[4]);
    const int num_runs = atoi(argv[5]);
    const char* output_file = argv[6];

    srand(time(NULL));

    struct Problem problem;
    problem.num_actions = num_actions;
    problem.variance = variance;
    problem.values = malloc(num_actions * sizeof(float));
    if (problem.values == NULL) {
        fprintf(stderr, "Memory allocation failed for problem.values\n");
        exit(1);
    }

    struct Agent agent;
    agent.epsilon = epsilon;
    agent.value_estimates = malloc(num_actions * sizeof(float));
    if (agent.value_estimates == NULL) {
        fprintf(stderr, "Memory allocation failed for agent.value_estimates\n");
        exit(1);
    }
    agent.action_counts = malloc(num_actions * sizeof(int));
    if (agent.action_counts == NULL) {
        fprintf(stderr, "Memory allocation failed for agent.action_counts\n");
        exit(1);
    }

    float* rewards = malloc(num_runs * num_steps * sizeof(float));
    if (rewards == NULL) {
        fprintf(stderr, "Memory allocation failed for rewards\n");
        exit(1);
    }

    run_trials(rewards, problem, agent, num_runs, num_steps);
    save_rewards(output_file, rewards, num_runs, num_steps);

    free(rewards);
    free(problem.values);
    free(agent.value_estimates);
    return 0;
}
