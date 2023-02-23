#ifndef BLUR_H
#define BLUR_H

#include <vector>

typedef std::vector< std::vector<float> > t_grid;

t_grid blur(t_grid &grid, float blurring);

#endif /* BLUR.H */