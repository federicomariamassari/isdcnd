#ifndef SENSE_H
#define SENSE_H

#include <vector>
#include <iostream>

typedef std::vector< std::vector<float> > t_grid;
typedef std::vector< std::vector<char> > t_char_grid;

t_grid sense(char color, t_char_grid &grid, t_grid &beliefs,  float p_hit, float p_miss);

#endif /* SENSE.H */