//
// Created by Joel Woodfield on 16/01/2025
//

#ifndef Q_H
#define Q_H

#include "mdp.h"

void train_q(Mdp* mdp, float** value, float gamma, float alpha, 
             float epsilon, int num_episodes);

#endif //Q_H