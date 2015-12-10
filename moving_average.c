//
//  moving_average.c
//  
//
//  Created by Jesus Gallegos  on 11/27/15.
//
//

#include "moving_average.h"

void filter(int* x_pos, int* y_pos, int* theta)
{
    // summing variables
    int i;
    int x_sum = 0;
    int y_sum = 0;
    int theta_sum = 0;
    
    // calulcate sum of last 10 values
    for (i = 0; i < 11; i++)
    {
        x_sum = x_sum+x_pos[i];
        y_sum = y_sum+y_pos[i];
        theta_sum = theta_sum+theta[i];
    }
    
    // calculate average
    x_pos[11] = x_sum/10;
    y_pos[11] = y_sum/10;
    theta[11] = theta_sum/10;
}