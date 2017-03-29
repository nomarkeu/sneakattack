#include "stdafx.h"
#include <array>
#include <vector>
#include <iostream>
#include "visibility.h"


int main()
{
	Triangles visibilityPolygon;
	Point observer = {1133.0,98.0};
	visibility(visibilityPolygon, observer);
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Map Generator");
	

	sf::VertexArray triangle(sf::Triangles, 3);

		
	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window.close();

		window.clear(sf::Color::White);
		window.draw(visibilityPolygon.triangles);
		window.display();
	}

	return 0;
}