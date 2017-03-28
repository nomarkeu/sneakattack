#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <utility>
#include "utilities.h"


void mapreader(vector<Segment>& linesegments, vector<Pointmap>& allpoints)
{
	//vector<std::pair<int, Point> > allpoints;

	linesegments.clear();
	std::ifstream map("map");
	if (map.is_open()) {
		Segment segment;
		std::array<sf::Vector2f, 4> points;
		char delimiter;
		int totalPointCounter = 0;
		while (map >> points[0].x >> delimiter >> points[0].y >> delimiter) {
			for (int i = 1; i != 4; i++)
				map >> points[i].x >> delimiter >> points[i].y >> delimiter;
			for (int i = 0; i != 3; i++) {
				allpoints.push_back(std::make_pair(totalPointCounter++, points[i]));
				segment = { points[i],points[i + 1] };
				linesegments.push_back(segment);
			}
			segment = { points[3], points[0] };
			allpoints.push_back(std::make_pair(totalPointCounter++, points[3]));
			linesegments.push_back(segment);
		}
	}
}