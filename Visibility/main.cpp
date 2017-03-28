#include "stdafx.h"
#include <SFML\Graphics.hpp>
#include <array>
#include <vector>
#include <iostream>
#include "utilities.h"

typedef std::array<sf::Vector2f, 2> Segment;
//void mapreader(std::vector<Segment>&);

int main()
{
	Triangles visibilityPolygon;
	Point observer = {1296.0,71.0};
	visibility(visibilityPolygon, observer);



	return 0;
}