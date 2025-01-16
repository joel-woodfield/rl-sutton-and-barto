//
// Created by Joel Woodfield on 16/01/2025
//

#ifndef EXPECTED_SARSA_H
#define EXPECTED_SARSA_H

#include "mdp.h"

void train_expected_sarsa(Mdp* mdp, float** value, float gamma, float alpha, 
                          float epsilon, int num_episodes);

#endif //EXPECTED_SARSA_H