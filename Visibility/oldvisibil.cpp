#include "stdafx.h"
#include "Visibility.hpp"
#include<SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>


int main()
{
	std::vector<geometry::LineSegment> segments;
	std::ifstream map("map");
	sf::Vector2f point1, point2;
	char comma;

	if (map.is_open()) {
		if (map >> point1.x >> comma >> point1.y) {
			sf::Vector2f start = point1;
			while (map >> point2.x >> comma >> point2.y) {
				segments.push_back(geometry::LineSegment(geometry::vec2(point1.x, point1.y), geometry::vec2(point2.x, point2.y)));

				point1 = point2;
			}
			segments.push_back(geometry::LineSegment(geometry::vec2(point1.x, point1 .y), geometry::vec2(start.x, start.y)));
		}
	}
	else
		throw std::runtime_error("Could not open file map");

		

	sf::ConvexShape visPol;

	visPol.setFillColor(sf::Color::Green);

	sf::ConvexShape visible(const sf::Vector2i& mouse, const std::vector<geometry::LineSegment>& segments);
	

	sf::ConvexShape room(6);
	room.setFillColor(sf::Color::Red);

	room.setPoint(0, sf::Vector2f(5, 5));
	room.setPoint(1, sf::Vector2f(400, 5));
	room.setPoint(2, sf::Vector2f(300, 300));
	room.setPoint(3, sf::Vector2f(800, 300));
	room.setPoint(4, sf::Vector2f(800, 600));
	room.setPoint(5, sf::Vector2f(5, 600));
			
		


	sf::RenderWindow window;
	window.create(sf::VideoMode(800, 600),
		"Visibility");

	sf::Vector2i mousePointer;

	while (window.isOpen()) {
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
			return 0;
		}
		
		mousePointer = sf::Mouse::getPosition(window);

		visPol.setFillColor(sf::Color::Red);
		visPol = visible(mousePointer, segments);

		window.clear();
		//window.draw(room);
		window.draw(visPol);
		window.display();

	}

	
	return 0;

}




sf::ConvexShape visible(const sf::Vector2i& mouse, const std::vector<geometry::LineSegment>& segments)
{

	geometry::vec2 pointt(mouse.x, mouse.y);
	std::vector<geometry::vec2> vecs = VisibilityPolygon(pointt, segments);

	sf::ConvexShape visPol(vecs.size());

	int i = 0;
	for (const auto& point : vecs) {
		visPol.setPoint(i, sf::Vector2f(point.element(0), point.element(1)));
		i++;
	}

	return visPol;

}
