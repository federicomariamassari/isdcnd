#include "headers/sense.h"

using namespace std;

t_grid sense(char color, t_char_grid &grid, t_grid &beliefs,  float p_hit, float p_miss) 
{
    vector<float>::size_type height = grid.size();
    vector<float>::size_type width = grid[0].size();
    int i, j;
    bool hit;

    for (i=0; i < height; i++) {
        for (j=0; j < width; j++) {

            hit = (color == grid[i][j]);
            beliefs[i][j] *= (hit * p_hit + (1-hit) * p_miss);
        }
    }

    return beliefs;
}
