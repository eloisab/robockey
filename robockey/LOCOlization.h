//
//  LOCOlization.h
//  ROBOCKEY
//
//  Created by Jesus Gallegos  on 11/13/15.
//
//

#ifndef __ROBOCKEY__LOCOlization__
#define __ROBOCKEY__LOCOlization__

#include <stdio.h>
char current_location(unsigned int* position);

int calc_dist(int x1, int y1, int x2, int y2);

char max_array(int a[], int num_elements, unsigned int* max_dat);

char min_array(int a[], int num_elements, unsigned int* min_dat);



#endif /* defined(__ROBOCKEY__LOCOlization__) */
