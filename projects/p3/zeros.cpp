#include "headers/zeros.h"

using namespace std;

t_grid zeros(int height, int width) {
	
	t_grid new_grid (height, vector<float> (width, 0.));
	
	return new_grid;
}