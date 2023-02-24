/**
	helpers.cpp

	Purpose: helper functions which are useful when
	implementing a 2-dimensional histogram filter.

	This file is incomplete! Your job is to make the
	normalize and blur functions work. Feel free to 
	look at helper.py for working implementations 
	which are written in python.
*/

#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <numeric>
#include "headers/helpers.h"
// #include "debugging_helpers.cpp"

using namespace std;

/**
	Normalizes a grid of numbers. 

    @param grid - a two dimensional grid (vector of vectors of floats)
		   where each entry represents the unnormalized probability 
		   associated with that grid cell.

    @return - a new normalized two dimensional grid where the sum of 
    	   all probabilities is equal to one.
*/
t_grid normalize(t_grid &grid) {
	
	vector<float>::size_type rows = grid.size();
	vector<float>::size_type cols = grid[0].size();

	// Initialize returned grid
	t_grid new_grid (rows, vector<float> (cols, 0.));

	int i, j;
	float sum = 0.;

	for (i=0; i < rows; i++) {
		sum += accumulate(grid[i].begin(), grid[i].end(), 0.);
	}

	for (i=0; i < rows; i++) {
		for (j=0; j < cols; j++) {
			new_grid[i][j] = grid[i][j] / sum;
		}
	}

	return new_grid;
}

/**
	Blurs (and normalizes) a grid of probabilities by spreading 
    probability from each cell over a 3x3 "window" of cells. This 
    function assumes a cyclic world where probability "spills 
    over" from the right edge to the left and bottom to top. 

    EXAMPLE - After blurring (with blurring=0.12) a localized 
    distribution like this:

    0.00  0.00  0.00 
    0.00  1.00  0.00
    0.00  0.00  0.00 

    would look like this:
	
	0.01  0.02	0.01
	0.02  0.88	0.02
	0.01  0.02  0.01

    @param grid - a two dimensional grid (vector of vectors of floats)
		   where each entry represents the unnormalized probability 
		   associated with that grid cell.

	@param blurring - a floating point number between 0.0 and 1.0 
		   which represents how much probability from one cell 
		   "spills over" to it's neighbors. If it's 0.0, then no
		   blurring occurs. 

    @return - a new normalized two dimensional grid where probability 
    	   has been blurred.
*/
t_grid blur(t_grid &grid, float blurring) {

	vector<float>::size_type height = grid.size();
	vector<float>::size_type width = grid[0].size();
	
	float center = 1. - blurring;
	float corner = blurring / 12.;
	float adjacent = blurring / 6.;

	t_grid window = {
		{corner, adjacent, corner}, 
		{adjacent, center, adjacent}, 
		{corner, adjacent, corner}
	};

	t_grid new_grid (height, vector<float> (width, 0.));

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
	
	return normalize(new_grid);
}

/**
    Determines when two grids of floating point numbers 
    are "close enough" that they should be considered 
    equal. Useful for battling "floating point errors".

    @param g1 - a grid of floats
    
    @param g2 - a grid of floats

    @return - A boolean (True or False) indicating whether
    these grids are (True) or are not (False) equal.
*/
bool close_enough(t_grid &g1, t_grid &g2) {
	
	int i, j;
	float v1, v2;

	vector<float>::size_type height_g1 = g1.size();
	vector<float>::size_type width_g1 = g1[0].size();

	vector<float>::size_type height_g2 = g2.size();
	vector<float>::size_type width_g2 = g2[0].size();

	if (height_g1 != height_g2) {
		return false;
	}

	if (width_g1 != width_g2) {
		return false;
	}

	for (i=0; i < height_g1; i++) {
		for (j=0; j < width_g1; j++) {
			
			v1 = g1[i][j];
			v2 = g2[i][j];
			
			if (abs(v2-v1) > 0.0001) {
				return false;
			}
		}
	}

	return true;
}

bool close_enough(float v1, float v2) { 
	return abs(v2-v1) <= 0.0001;
}

/**
    Helper function for reading in map data

    @param s - a string representing one line of map data.

    @return - A row of chars, each of which represents the
    color of a cell in a grid world.
*/
vector<char> read_line(string s) {

	vector<char> row;

	size_t pos = 0;
	string token;
	string delimiter = " ";
	char cell;

	while ((pos = s.find(delimiter)) != std::string::npos) {
		token = s.substr(0, pos);
		s.erase(0, pos + delimiter.length());

		cell = token.at(0);
		row.push_back(cell);
	}

	return row;
}

/**
    Helper function for reading in map data

    @param file_name - The filename where the map is stored.

    @return - A grid of chars representing a map.
*/
t_char_grid read_map(string file_name) {

	ifstream infile(file_name);
	t_char_grid map;
	
	if (infile.is_open()) {

		char color;
		vector <char> row;
		
		string line;

		while (getline(infile, line)) {

			row = read_line(line);
			map.push_back(row);
		}
	}
	return map;
}

/**
    Creates a grid of zeros

    For example:

    zeros(2, 3) would return

    0.0  0.0  0.0
    0.0  0.0  0.0

    @param height - the height of the desired grid

    @param width - the width of the desired grid.

    @return a grid of zeros (floats)
*/
t_grid zeros(int height, int width) {
	t_grid new_grid (height, vector<float> (width, 0.));
	return new_grid;
}

// int main() {
// 	vector < vector < char > > map = read_map("maps/m1.txt");
// 	show_grid(map);
// 	return 0;
// }
