#ifndef SIMULATE_H
#define SIMULATE_H

#include <vector>

typedef std::vector< std::vector<float> > t_grid;
typedef std::vector< std::vector<char> > t_char_grid;

class Simulation {
	
private:
	std::vector<char> get_colors();

public: 
	t_char_grid grid;
	t_grid beliefs;

	float blur, p_hit, p_miss, incorrect_sense_prob;

	int height, width, num_colors;
	
	std::vector<int> true_pose;
	std::vector<int> prev_pose;

	std::vector<char> colors;
	Simulation(t_char_grid, float, float, std::vector<int>);

};

#endif /* SIMULATE_H */