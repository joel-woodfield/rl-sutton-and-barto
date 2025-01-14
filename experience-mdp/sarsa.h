//
// Created by Joel Woodfield on 13/01/2025
//

#ifndef SARSA_H
#define SARSA_H

#include "mdp.h"

void train_sarsa(Mdp* mdp, float** value, float gamma, float alpha,
                 float epsilon, int num_episodes);

#endif //SARSA_H