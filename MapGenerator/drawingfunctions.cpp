#include "drawingfunctions.h"

void drawline(const Point& startpoint, sf::VertexArray&  MapLines, int& vertexnumber, sf::RenderWindow& window)
{
	int i = vertexnumber;
	bool leftClick = false;
	bool rightClick = false;
	bool draw = false;
	bool secondPointSet = false;
	bool start = true;
	bool canStartANewLine = true;

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
		MapLines[i + 1].position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

	if (canStartANewLine && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		canStartANewLine = false;
		i += 2;
		MapLines.append(MapLines[i - 1]);
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

}