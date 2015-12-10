//
//  LOCOlization.c
//  ROBOCKEY
//
//  Created by Jesus Gallegos  on 11/13/15.
//
//

#define _GNU_SOURCE
#include <stdio.h>
#include "LOCOlization.h"
#include "m_general.h"
#include "math.h"
#include "m_wii.h"
#include "m_bus.h"

float NaN = 0.0/0.0;


char current_location(int* position)
{
    // int buffer to hold blob data
    unsigned int buffer[12];
    
    // read wii camera blob data into int buffer
    m_wii_read(buffer);
    
    // star points
    int x1 = (int)buffer[0];
    int y1 = (int)buffer[1];
    int x2 = (int)buffer[3];
    int y2 = (int)buffer[4];
    int x3 = (int)buffer[6];
    int y3 = (int)buffer[7];
    int x4 = (int)buffer[9];
    int y4 = (int)buffer[10];
    
    // array of points
    int x_points[4] = {x1, x2, x3, x4};
    int y_points[4] = {y1, y2, y3, y4};
    
    // lose star case
    int i;
    for(i = 0; i<=4;i++)
    {
        if (x_points[i]==1023 && y_points[i]==1023)
        {
            x_points[i] = NaN;
            y_points[i] = NaN;
        }
    }
    
    // calculate all possible distances
    int d12 = calc_dist(x_points[0], y_points[0], x_points[1], y_points[1]);
    int d13 = calc_dist(x_points[0], y_points[0], x_points[2], y_points[2]);
    int d14 = calc_dist(x_points[0], y_points[0], x_points[3], y_points[3]);
    int d23 = calc_dist(x_points[1], y_points[1], x_points[2], y_points[2]);
    int d24 = calc_dist(x_points[1], y_points[1], x_points[3], y_points[3]);
    int d34 = calc_dist(x_points[2], y_points[2], x_points[3], y_points[3]);
    
    // store all distances in an array
    int all_distances[6] = {d12,d13,d14,d23,d24,d34};
    
    // store all pair
    int all_pairs[6][2] = {{0,1},{0,2},{0,3},{1,2},{1,3},{2,3}};
    
    // index and value of max and min distance
    int max_dat[2];
    int min_dat[2];

    // find min and max arrays
    max_array(all_distances, 6, max_dat);
    min_array(all_distances, 6, min_dat);
    
    // index of max and min points
    int max_index = max_dat[1];
    int max = max_dat[0];
    int min_index = min_dat[1];

    // array of pair indicies
    int long_pair[2] = {all_pairs[max_index][0], all_pairs[max_index][1]};
    int short_pair[2] = {all_pairs[min_index][0], all_pairs[min_index][1]};
    
    int top_point[2];
    int bottom_point[2];
    
    // finds top and bottom points
    if (long_pair[0] == short_pair[0] || long_pair[0] == short_pair[1])
    {
        top_point[0] = x_points[long_pair[0]];
        top_point[1] = y_points[long_pair[0]];
        bottom_point[0] = x_points[long_pair[1]];
        bottom_point[1] = y_points[long_pair[1]];
    }
    else
    {
        top_point[0] =x_points[long_pair[1]];
        top_point[1] =y_points[long_pair[1]];
        bottom_point[0] =x_points[long_pair[0]];
        bottom_point[1] =y_points[long_pair[0]];

    }
    
    // calculate center of rink
    double x_center = ((double)top_point[0] + (double)bottom_point[0])/2;
    double y_center = ((double)top_point[1] + (double)bottom_point[1])/2;
    
    //double theta = acos(y_unit);
    double x_diff = (double)top_point[0] - x_center;
    double y_diff =(double)top_point[1] - y_center;
    
    // calculate position of camera relative to camera coordinate axes
    double camera_x = 512;
    double camera_y = 384;
    
    // calculate angle theta
    double theta = atan2(x_diff, y_diff);

    // rotated points
    float rotated_x = ((((camera_x-x_center)*cos(theta)) + ((camera_y-y_center)*-sin(theta))) + camera_x) - camera_x;
    float rotated_y = ((((camera_x-x_center)*sin(theta)) + ((camera_y-y_center)*cos(theta))) + camera_y) - camera_y;

    // position and angle relative to rink axes
    position[0] = (int) (29*(rotated_x))/max;
    position[1] = (int) (29*(rotated_y))/max;
    position[2] = (int) (theta*(180/M_PI));
    
    return 1;
    }

int calc_dist(int x1, int y1, int x2, int y2)
{
    double delta_x = x1 - x2; // diff in x
    double delta_y = y1 - y2; // diff in x
    
    // calc distance
    double distance = hypot(delta_x,delta_y);
    
    return (int) distance;
}

char max_array(int a[], int num_elements, int* max_dat)
{
    int i;
    int index;
    int max=-16000; // set max to some small number
    
    for (i=0; i<num_elements; i++) // for each distance
    {
        // find new max
        if (a[i]>max)
        {
            max=a[i];
            index = i;
        }
    }
    
    // if less than min poss distance
    if (max < 0 ) {return 0;}
    max_dat[0] = max;
    max_dat[1] = index;
    return 1;
}

char min_array(int b[], int num_elements, int* min_dat)
{
    int i;
    int index;
    int min= 32000; // set max to some small number
    
    for (i=0; i<num_elements; i++) // for each distance
    {
        // find new max
        if (b[i]<min)
        {
            min=b[i];
            index = i;
        }
    }
    // if greater than max poss distance
    if (min > 32000 ) {return 0;}
    min_dat[0] = min;
    min_dat[1] = index;
    return 1;
}


