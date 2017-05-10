#OLD VERSION

#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#include <fstream>

using std::vector;

int main()
{
	sf::Vector2f startpoint;
	sf::Vector2f endpoint;
	bool draw = false;
	bool undotrigger = false;
	bool undo = false;
	vector<sf::RectangleShape> rectangles;
	sf::Vector2f rectanglesize;
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Map Generator");
	sf::Rect<float> rect(static_cast<sf::Vector2<float> >(window.getPosition()), static_cast<sf::Vector2<float> >(window.getSize()));

	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setOutlineThickness(2);

	sf::Event event;
	//start drawing
	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;

		window.clear(sf::Color::White);

		// if you're not already drawing a rectangle and if left mouse button is clicked, start drawing rectangle
		if (!draw && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			startpoint = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
			if (rect.contains(startpoint)) {
				draw = true;
				rectangle.setPosition(startpoint);
			}
		}
		// if currently drawing and leftmousebutton was released, stop drawing and store the drawn rectangle
		else if (draw && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) { 
			draw = false;
			rectangles.push_back(rectangle);
		}

		// if currently drawing a rectangle, display rectangle and continue drawing
		if (draw == true) {
			endpoint = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));
			rectanglesize = sf::Vector2f(endpoint.x - startpoint.x, endpoint.y - startpoint.y);
			rectangle.setSize(rectanglesize);
			window.draw(rectangle);
		}

		//if Ctr-Z is triggered, remove last drawn rectangle
		if (!rectangles.empty()) {
			undotrigger = !draw && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z);
			if (!undo && undotrigger)
				undo = true;
			if (undo && !undotrigger) {
				rectangles.pop_back();
				undo = false;
				draw = false;
			}
		}

        // draw all the rectangles
		for (auto& rectangle_ : rectangles)
			window.draw(rectangle_);
		
		window.display();
} 

	//write drawn rectangles to file
	if (!rectangles.empty()) {
		std::ofstream map("map");

		while (map.is_open()) {
			map.clear();
			sf::Transform transform;
			sf::Vector2f point;
			vector<int> vertex({ 0,1,2,3 });
			for (auto& rectangle_ : rectangles) {
				transform = rectangle_.getTransform();
				for (auto& i : vertex) {
					point = rectangle_.getPoint(i);
					point = transform.transformPoint(point);
					map << point.x << "," << point.y << ";";
				}
				map << std::endl;
			}
			map.close();
		}
	}
	window.close();
	
	return 0;
}