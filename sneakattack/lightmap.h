#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "RectangleMap.h"
#include "visibilitypolygon.h"
// namespace which handles all the lighting related functions.


typedef sf::Vector2i Pointi;


namespace light
{
	extern std::vector<sf::Vertex> lightMap;
	extern sf::VertexArray lightTiles;
	extern RectangleMap*  Map;
	extern Triangles lightPolygon;
	
		
	void turnOn(Pointi& light);
	void init( RectangleMap* const map_);
	void updateTiles();
}