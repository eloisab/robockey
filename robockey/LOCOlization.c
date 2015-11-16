//
//  LOCOlization.c
//  ROBOCKEY
//
//  Created by Jesus Gallegos  on 11/13/15.
//
//

#include "LOCOlization.h"
#include "m_general.h"
#include "math.h"
#include "m_wii.h"
#include "m_bus.h"


char current_location(unsigned int* position)
{
    // int buffer to hold blob data
    unsigned int buffer[12] ={500, 500, 2, 500, 500, 3, 500, 500, 4, 500, 500,3};
    //buffer[12] = {500, 500, 2, 500, 500, 3, 500, 500, 4, 500, 500,3};
    
    // initialize m_bus communications
    // and open wii camera
    m_bus_init();
    m_wii_open();
    
    // read wii camera blob data into int buffer
    m_wii_read(buffer);
   
    /*
    // points
    int x1 = buffer[0];
    int y1 = buffer[1];
    int x2 = buffer[3];
    int y2 = buffer[4];
    int x3 = buffer[6];
    int y3 = buffer[7];
    int x4 = buffer[9];
    int y4 = buffer[10];
    */
    
    //int size = 4;
    
    int i;
    unsigned int *x_points[4]; // ptrs to array of x points
    unsigned int *y_points[4]; // ptrs to array of y points
    int j = 0;
    for (i = 0; i < 10; i+=3)
    {   // i = 0, 3, 6 ,9
        x_points[j] =&buffer[i];
        j++;
    }
    int k = 0;;
    for (i = 1; i < 11; i+=3)
    {   // i = 1, 4, 7, 10
        y_points[k] = &buffer[i];
        k++;
    }
    
    // calculate all possible distances
    int d12 = calc_dist(*x_points[0], *y_points[0], *x_points[1], *y_points[1]);
    int d13 = calc_dist(*x_points[0], *y_points[0], *x_points[2], *y_points[2]);
    int d14 = calc_dist(*x_points[0], *y_points[0], *x_points[3], *y_points[3]);
    int d23 = calc_dist(*x_points[1], *y_points[1], *x_points[2], *y_points[2]);
    int d24 = calc_dist(*x_points[1], *y_points[1], *x_points[3], *y_points[3]);
    int d34 = calc_dist(*x_points[2], *y_points[2], *x_points[3], *y_points[3]);
    
    // store all distances in an array
    int all_distances[6] = {d12,d13,d14,d23,d24,d34};
    
    // store distance pair points
    int pair1[2] = {0,1};
    int pair2[2] = {0,2};
    int pair3[2] = {0,3};
    int pair4[2] = {1,2};
    int pair5[2] = {1,3};
    int pair6[2] = {2,3};
    
    // pointer to pairs
    int *all_pairs[6] = {pair1, pair2, pair3, pair4, pair5, pair6};
                        
    // store all the pairs
    //int all_pairs[12] = {1,2,1,3,1,4,2,3,2,4,3,4};
    
    // index and value of max and min distance
    unsigned int max_dat[2];
    unsigned int min_dat[2];

    // fill min and max arrays
    max_array(all_distances, 6, max_dat);
    min_array(all_distances, 6, min_dat);
    
    // extract max and min data
    //int max_d = max_dat[0];
    //int min_d = min_dat[0];
    
    // index of max and min points
    unsigned int max_index = max_dat[1];
    unsigned int min_index = min_dat[1];

    // pair of points closest and farthest apart
    int long_pair[2] = {*(all_pairs[max_index] + 0), *(all_pairs[max_index] + 1)};
    int short_pair[2] = {*(all_pairs[min_index] + 0), *(all_pairs[min_index] + 1)};
    
    // extract all 4 points
    unsigned int point1[2] = {*x_points[long_pair[0]], *y_points[long_pair[0]]};
    unsigned int point2[2] = {*x_points[long_pair[1]], *y_points[long_pair[1]]};
    unsigned int point3[2] = {*x_points[short_pair[0]], *y_points[short_pair[0]]};
    unsigned int point4[2] = {*x_points[short_pair[1]], *y_points[short_pair[1]]};

    // find top and bottom point!
    unsigned int *top_point;
    unsigned int *bottom_point;
    
    if (point1 == point3)
    {
        top_point = point1;
        bottom_point = point2;
    }
    else if (point1 == point4)
    {
        top_point = point1;
        bottom_point = point2;
    }
    else if (point2 == point3)
    {
        top_point = point2;
        bottom_point = point1;
    }
    else if (point2 == point4)
    {
        top_point = point2;
        bottom_point = point1;
    }
    else
    {
        top_point = point1;
        bottom_point = point2;
    }
    
    unsigned int x_diff = *(top_point + 0) - *(bottom_point + 0);
    unsigned int y_diff = *(top_point + 1) - *(bottom_point + 1);
    
    
    // calculate angle of camera relative to rink coordinate axes
    double theta = atan2((double) y_diff, (double) x_diff);
    
    // rotation matrix
    double rot[2][2] = {
        {cos(theta), -sin(theta)},
        {sin(theta), cos(theta)}
    };
    
    // rotated top and bottom points
    double rotated_top[2] = {*(top_point + 0)*rot[0][0] + *(top_point + 1)*rot[0][1], *(top_point + 0)*rot[1][0] + *(top_point + 1)*rot[1][1]};
    double rotated_bottom[2] ={*(bottom_point + 0)*rot[0][0] + *(bottom_point + 1)*rot[0][1],
        *(bottom_point + 0)*rot[1][0] + *(bottom_point + 1)*rot[1][1]};
    
    // rotate center of camera
    double L = 512*rot[0][0] + 384*rot[0][1];
    double W = 512*rot[1][0] + 384*rot[1][1];

    // find origin
    double x0 = (rotated_top[0] + rotated_bottom[0])/2;
    double y0 = (rotated_top[1] + rotated_bottom[1])/2;
    
    // current position
    int x_position = (int) L - x0;
    int y_position = (int) W - y0;

    position[0] = (unsigned int) x_position;
    position[1] = (unsigned int) y_position;
    position[2] = (unsigned int) theta*(180/M_PI);;
    
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

char max_array(int a[], int num_elements, unsigned int* max_dat)
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

char min_array(int b[], int num_elements, unsigned int* min_dat)
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


