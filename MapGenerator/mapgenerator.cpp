#include "stdafx.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "drawingfunctions.h"

using std::vector;

int main()
{

	
	bool undotrigger = false; //1299 768
	bool undo = false;
	vector<sf::RectangleShape> rectangles;
	sf::Vector2f rectanglesize;
	sf::RenderWindow window(sf::VideoMode(800, 600), "Map Generator");//,sf::Style::Fullscreen);
	sf::Rect<float> rect(static_cast<sf::Vector2<float> >(window.getPosition()), static_cast<sf::Vector2<float> >(window.getSize()));

	sf::VertexArray MapLines(sf::Lines);
	
	sf::Texture texture;
	if (!texture.loadFromFile("background.jpg"))
		throw std::runtime_error("Could not load file player.png");


	sf::Sprite background;
	background.setTexture(texture);
	background.setTextureRect(sf::IntRect(0, 0, 1920, 1200));
	background.setScale(sf::Vector2f(.64, .64));

	bool leftClick = false;
	bool rightClick = false;
	bool draw = false;
	bool secondPointSet = false;
	bool start = true;
	bool canStartANewLine = true;

	int i = 0;
	sf::Vector2f startpoint;
	sf::Vector2f endpoint;

	//sf::Event event;
	//start drawing

	//draw is always false in this loop level
	while (window.isOpen()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;
		

		drawline(startpoint, MapLines, i, window);

		
				
		if (!draw && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			//start = false;
			draw = true;
			

			MapLines.append(sf::Vertex(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))));
			MapLines[i].color = sf::Color::Red;
			MapLines.append(sf::Vertex(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))));
			MapLines[i + 1].color = sf::Color::Red;
		}

		

		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && draw)
			canStartANewLine = true;
	
			
		if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && draw)
			MapLines[i+1].position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

		if (canStartANewLine && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			canStartANewLine = false;
			i += 2;
			MapLines.append(MapLines[i-1]);
			MapLines[i].color = sf::Color::Red;
			MapLines.append(sf::Vertex(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))));
			MapLines[i + 1].color = sf::Color::Red;
			}


		if (draw && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			draw = false;
		//	i = i - 2;
		//	MapLines.c
			MapLines.resize(MapLines.getVertexCount() - 2);
			
		}

		window.clear(sf::Color::White);

		window.draw(background);
		window.draw(MapLines);
		
		window.display();
} 


	window.close();
	
	return 0;
}