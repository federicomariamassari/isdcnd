#ifndef LOCALIZER_H
#define LOCALIZER_H

#include <vector>

typedef std::vector< std::vector<float> > t_grid;
typedef std::vector< std::vector<char> > t_char_grid;

// Initializes a grid of beliefs to a uniform distribution. 
t_grid initialize_beliefs(t_char_grid &grid);

/**    
    Implements robot sensing by updating beliefs based on the 
    color of a sensor measurement 
*/
t_grid sense(char color, t_char_grid &grid, t_grid &beliefs, float p_hit, float p_miss);

/**
    Implements robot motion by updating beliefs based on the 
    intended dx and dy of the robot. 
*/
t_grid move(int dy, int dx, t_grid &beliefs, float blurring);

#endif /* LOCALIZER_H */