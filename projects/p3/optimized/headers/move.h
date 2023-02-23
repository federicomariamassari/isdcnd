#ifndef MOVE_H
#define MOVE_H

#include <vector>
#include <iostream>

typedef std::vector< std::vector<float> > t_grid;

t_grid move(int dy, int dx, t_grid &beliefs); 

#endif /* MOVE.H */
