#ifndef INITIALIZE_BELIEFS_H
#define INITIALIZE_BELIEFS_H

#include <vector>

typedef std::vector< std::vector<float> > t_grid;
typedef std::vector< std::vector<char> > t_char_grid;

t_grid initialize_beliefs(t_char_grid &grid);

#endif /* INITIALIZE_BELIEFS.H */
