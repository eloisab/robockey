//
//  moving_average.h
//  
//
//  Created by Jesus Gallegos  on 11/27/15.
//
//

#ifndef ____moving_average__
#define ____moving_average__

#include <stdio.h>

void filter(int* x_pos, int* y_pos, int* theta);
// FUNCTIONALITY
// calculates average of the last 10 x, y and theta values
// and stores them as the 11th value in an array
//
// TAKES:
// pointer to integer arrays of x, y and theta values
//
// RETURNS:
// nothing

#endif /* defined(____moving_average__) */
