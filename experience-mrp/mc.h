//
// Created by Joel Woodfield on 09/01/2025.
//

#ifndef MC_H
#define MC_H

#include "mrp.h"

void train_mc(Mrp* mrp, float* value, float gamma, float alpha, 
              int num_episodes);

#endif //MC_H
