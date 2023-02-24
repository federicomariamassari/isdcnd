/**
    localizer.cpp

    Purpose: implements a 2-dimensional histogram filter
    for a robot living on a colored cyclical grid by 
    correctly implementing the "initialize_beliefs", 
    "sense", and "move" functions.
*/

#include <stdlib.h>
#include "headers/localizer.h"
#include "helpers.cpp"
#include "debugging_helpers.cpp"

using namespace std;

/**
    Initializes a grid of beliefs to a uniform distribution. 

    @param grid - a two dimensional grid map (vector of vectors 
           of chars) representing the robot's world. For example:
           
           g g g
           g r g
           g g g
           
           would be a 3x3 world where every cell is green except 
           for the center, which is red.

    @return - a normalized two dimensional grid of floats. For 
           a 2x2 grid, for example, this would be:

           0.25 0.25
           0.25 0.25
*/
t_grid initialize_beliefs(t_char_grid &grid) {

    int height = grid.size();
    int width = grid[0].size();
    int area = height * width;

    t_grid beliefs (height, vector<float> (width, 1. / area));
    
    return beliefs;
}

/**
    Implements robot motion by updating beliefs based on the 
    intended dx and dy of the robot. 

    For example, if a localized robot with the following beliefs

    0.00  0.00  0.00
    0.00  1.00  0.00
    0.00  0.00  0.00 

    and dx and dy are both 1 and blurring is 0 (noiseless motion),
    than after calling this function the returned beliefs would be

    0.00  0.00  0.00
    0.00  0.00  0.00
    0.00  0.00  1.00 

  @param dy - the intended change in y position of the robot

  @param dx - the intended change in x position of the robot

    @param beliefs - a two dimensional grid of floats representing
         the robot's beliefs for each cell before sensing. For 
         example, a robot which has almost certainly localized 
         itself in a 2D world might have the following beliefs:

         0.01 0.98
         0.00 0.01

    @param blurring - A number representing how noisy robot motion
        is. If blurring = 0.0 then motion is noiseless.

    @return - a normalized two dimensional grid of floats 
         representing the updated beliefs for the robot. 
*/
t_grid move(int dy, int dx, t_grid &beliefs, float blurring)
{
    int height = beliefs.size();
    int width = beliefs[0].size();
    int i, j, row, col;

      t_grid new_grid (height, vector<float> (width, 0.));

      for (i=0; i < height; i++) {
        for (j=0; j < width; j++) {
            
            row = ((i + dy) % height + height) % height;
            col = ((j + dx) % width + width) % width;

            new_grid[row][col] = beliefs[i][j];
        }
    }

    return blur(new_grid, blurring);
}


/**
    Implements robot sensing by updating beliefs based on the 
    color of a sensor measurement 

    @param color - the color the robot has sensed at its location

    @param grid - the current map of the world, stored as a grid
           (vector of vectors of chars) where each char represents a 
           color. For example:

           g g g
           g r g
           g g g

       @param beliefs - a two dimensional grid of floats representing
              the robot's beliefs for each cell before sensing. For 
              example, a robot which has almost certainly localized 
              itself in a 2D world might have the following beliefs:

              0.01 0.98
              0.00 0.01

    @param p_hit - the RELATIVE probability that any "sense" is 
           correct. The ratio of p_hit / p_miss indicates how many
           times MORE likely it is to have a correct "sense" than
           an incorrect one.

       @param p_miss - the RELATIVE probability that any "sense" is 
           incorrect. The ratio of p_hit / p_miss indicates how many
           times MORE likely it is to have a correct "sense" than
           an incorrect one.

    @return - a normalized two dimensional grid of floats 
           representing the updated beliefs for the robot. 
*/
t_grid sense(char color, t_char_grid &grid, t_grid &beliefs, float p_hit, float p_miss) 
{
    int height = grid.size();
    int width = grid[0].size();
    int i, j;
    bool hit;

      t_grid new_beliefs (height, vector<float> (width, 0.));

    for (i=0; i < height; i++) {
        for (j=0; j < width; j++) {

            hit = (color == grid[i][j]);
            new_beliefs[i][j] = beliefs[i][j] * (hit * p_hit + (1-hit) * p_miss);
        }
    }

    return normalize(new_beliefs);
}