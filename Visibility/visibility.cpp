#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include "utilities.h"
// implement collinear check

void visibility(Triangles& visibilityPolygon,Point observer)
{
	
	sf::VertexArray visibleTriangle(sf::Triangles, 3);

	//sort(linesegments.begin(), linesegments.end());
		
	AngleComparator compare(observer);

	vector<Segment> linesegments;
	vector<Pointmap> allpoints;
	mapreader(linesegments, allpoints);
	for (auto point : allpoints) {
		std::cout << point.first<<": "<<point.second.x << ", " << point.second.y << std::endl;
	}
	std::cout << "-----------" << std::endl;
	getchar();

	//for (auto a : allpoints)
	//	for (auto b : allpoints)
	//		std::cout << compare(a, b)<<std::endl;
	//getchar();


	sort(allpoints.begin(), allpoints.end(), compare);
	for (auto point : allpoints) {
		std::cout << point.first << ": "<<point.second.x << ", " << point.second.y << std::endl;
	}
	
	getchar();
}




