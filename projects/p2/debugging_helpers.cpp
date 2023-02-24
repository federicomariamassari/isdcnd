/**
	debugging_helpers.cpp
	
	Purpose: helper functions for debugging when working
	with grids of floats and chars.
*/

#include <vector>
#include "headers/debugging_helpers.h"

using namespace std;

/**
    Displays a grid of beliefs. Does not return.

    @param grid - a two dimensional grid (vector of 
    	   vectors of floats) which will usually 
    	   represent a robot's beliefs.
*/
void show_grid(t_grid grid) {
	int i, j;
	float p;
	vector<float> row;
	for (i = 0; i < grid.size(); i++)
	{
		row = grid[i];
		for (j=0; j< row.size(); j++)
		{
			p = row[j];	
			cout << p << ' ';
		}
		cout << endl;
	}
}

/**
    Displays a grid map of the world
*/
void show_grid(t_char_grid map) {
	int i, j;
	char p;
	vector<char> row;
	for (i = 0; i < map.size(); i++)
	{
		row = map[i];
		for (j=0; j< row.size(); j++)
		{
			p = row[j];	
			cout << p << ' ';
		}
		cout << endl;
	}
}

