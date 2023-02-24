#ifndef HELPERS_H
#define HELPERS_H

#include <vector>
#include <string>

typedef std::vector< std::vector<float> > t_grid;

// Normalizes a grid of numbers. 
t_grid normalize(t_grid &grid);

/** 
	Blurs (and normalizes) a grid of probabilities by spreading 
	probability from each cell over a 3x3 "window" of cells. This 
	function assumes a cyclic world where probability "spills 
	over" from the right edge to the left and bottom to top.
*/
t_grid blur(t_grid &grid, float blurring);

/**
    Determines when two grids of floating point numbers 
    are "close enough" that they should be considered 
    equal. Useful for battling "floating point errors".
*/
bool close_enough(t_grid &g1, t_grid &g2);

bool close_enough(float v1, float v2);

// Helper function for reading in map data
std::vector <char> read_line(std::string s);

// Helper function for reading in map data
t_char_grid read_map(std::string file_name);

// Creates a grid of zeros
t_grid zeros(int height, int width);

#endif /* HELPERS_H */