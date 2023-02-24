#ifndef DEBUGGING_HELPERS_H
#define DEBUGGING_HELPERS_H

#include <vector>

typedef std::vector< std::vector<float> > t_grid;
typedef std::vector< std::vector<char> > t_char_grid;

// Displays a grid of beliefs. Does not return.
void show_grid(t_grid grid);

// Displays a grid map of the world
void show_grid(t_char_grid map);

#endif /* DEBUGGING_HELPERS_H */