#include "headers/initialize_beliefs.h"

using namespace std;

t_grid initialize_beliefs(t_char_grid &grid) {

	vector<float>::size_type height = grid.size();
	vector<float>::size_type width = grid[0].size();
 
	float area = height * width;

  	t_grid new_grid (height, vector<float> (width, 1. / area));

	return new_grid;
}