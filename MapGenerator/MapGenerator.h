#pragma once
#include "SFML\Graphics.hpp"
#include "tilemap.h"

typedef sf::Vector2f Point;
typedef sf::Vector2f Vector;


class MapGenerator {
private:
	

	bool draw = false;
	bool canStartANewLine = false;
	bool lineAttached;
	bool finishing;
	int i = 0;
	int newLineSetStart;
	float attachDistanceSquared = 350.f;
	sf::VertexArray attachPointCross;
	Point attachPoint;

	sf::RenderWindow window;
	sf::VertexArray MapLines;
	TileMap background;
	sf::Texture texture;


	void drawline();
	Point intersection(const Point&, const Point&, const Point&);
	bool isClose(const Point&, const Point&, const Point&);
	int attach(Point&);
	Point findAttachPoint(Point&, int&);
	void writeToFile();
	void readTileMap();
	

public:
	MapGenerator() : attachDistanceSquared(350.f), i(0), draw(false),canStartANewLine(false), attachPointCross(sf::Lines, 4), lineAttached(false), finishing(false) {
		window.create(sf::VideoMode(1100, 700), "Map Generator");
		MapLines.setPrimitiveType(sf::Lines);
		for (int j = 0; j != 4; j++)
			attachPointCross[j].color = sf::Color::Blue;
		readTileMap();
	}

	void start();
};