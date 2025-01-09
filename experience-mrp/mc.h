//
// Created by Joel Woodfield on 09/01/2025.
//

#ifndef MC_H
#define MC_H

#include "mrp.h"

void train_mc(Mrp* mrp, int (*init_mrp)(Mrp*), StateRewardPair (*step_mrp)(Mrp*, int), 
           int (*s2i_mrp)(int), float* value, float gamma, float alpha, int num_episodes);

#endif //MC_H
