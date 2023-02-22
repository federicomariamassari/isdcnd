#include "headers/normalize.h"
#include "headers/zeros.h"

using namespace std;

t_grid normalize(t_grid &grid) {
	
	vector<float>::size_type height = grid.size();
	vector<float>::size_type width = grid[0].size();

	t_grid new_grid = zeros(height, width);

	int i, j;
	float sum = 0.;

	for (i=0; i < height; i++) {
		sum += accumulate(grid[i].begin(), grid[i].end(), 0.);
	}

	for (i=0; i < height; i++) {
		for (j=0; j < width; j++) {
			new_grid[i][j] = grid[i][j] / sum;
		}
	}

	return new_grid;
}
