#pragma once
#include <SFML\Graphics.hpp>

typedef sf::Vector2f Point;

void drawline(const Point& startpoint, sf::VertexArray&  MapLines, int& vertexnumber, sf::RenderWindow& window);