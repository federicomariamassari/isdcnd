#include "headers/move.h"
#include "headers/zeros.h"

using namespace std;

t_grid move(int dy, int dx, t_grid &beliefs) 
{
	int height = beliefs.size();
	int width = beliefs[0].size();
	int i, j, row, col;

	t_grid new_grid = zeros(height, width);

	for (i=0; i < height; i++) {
		for (j=0; j < width; j++) {
			
			row = ((i + dy) % height + height) % height;
			col = ((j + dx) % width + width) % width;

			new_grid[row][col] = beliefs[i][j];
		}
	}
  	
	return new_grid;
}
