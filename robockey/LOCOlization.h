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
char current_location(int* position);
// FUNCTIONALITY
// Finds the current ocation of the robot relative to the rink coordinate axes
//
// TAKES:
// pointer to an integer array
//
// RETURNS:
// char: 1 if succesful, 0 if not

int calc_dist(int x1, int y1, int x2, int y2);
// FUNCTIONALITY
// calculates distance betwen 2 points
//
// TAKES:
// x an y position of two points
//
// RETURNS:
// Ineteger: Distance

char max_array(int a[], int num_elements, int* max_dat);
// FUNCTIONALITY
// Calculate maximum value and index if max value in an array
//
// TAKES:
// Array
// number of elements in the array
// pointer to array contaiing max and index
//
// RETURNS:
// char: 1 if succesful

char min_array(int b[], int num_elements, int* min_dat);
// FUNCTIONALITY
// Calculate min value and index if min value in an array
//
// TAKES:
// Array
// number of elements in the array
// pointer to array contaiing min and index
//
// RETURNS:
// char: 1 if succesful


#endif /* defined(__ROBOCKEY__LOCOlization__) */
