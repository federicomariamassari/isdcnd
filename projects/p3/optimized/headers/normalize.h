#ifndef NORMALIZE_H
#define NORMALIZE_H

#include <vector>
#include <numeric>

typedef std::vector< std::vector<float> > t_grid;

t_grid normalize(t_grid &grid);

#endif /* NORMALIZE.H */