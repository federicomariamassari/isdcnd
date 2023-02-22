#include "headers/blur.h"
#include "headers/zeros.h"
#include "headers/print.h"

using namespace std;

t_grid blur(t_grid &grid, float blurring) {

	vector<float>::size_type height = grid.size();
	vector<float>::size_type width = grid[0].size();
	
	static float center = 1. - blurring;
	static float corner = blurring / 12.;
	static float adjacent = blurring / 6.;

	static t_grid window = {
		{corner, adjacent, corner}, 
		{adjacent, center, adjacent}, 
		{corner, adjacent, corner}
	};

	t_grid new_grid = zeros(height, width);

	float multiplier;
	int i, j, dx, dy, row, col;

	for (i=0; i < height; i++) {
		for (j=0; j < width; j++) {

			for (dx = -1; dx < 2; dx++) {
				for (dy = -1; dy < 2; dy++) {

					multiplier = window[dx+1][dy+1];

					row = ((i + dy) % height + height) % height;
					col = ((j + dx) % width + width) % width;

					new_grid[row][col] += (multiplier * grid[i][j]);
				}
			}
		}
	}

	return new_grid;
}
