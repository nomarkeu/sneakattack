#include "stdafx.h"
#include <array>
#include <vector>
#include <iostream>
#include "visibility.h"
#include "map.h"


int main()
{
	Triangles visibilityPolygon;
	vector<Segment> linesegments; //map
	Point observer = {500.0,200.0};
	visibility(visibilityPolygon, observer, linesegments);
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Visibility");
	

	RectangleMap map(linesegments);

	sf::VertexArray triangle(sf::Triangles, 3);

		
	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		window.clear(sf::Color::White);
		window.draw(visibilityPolygon.triangles);
		window.draw(map);
		window.display();
	}

	return 0;
}