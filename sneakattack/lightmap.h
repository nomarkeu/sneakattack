#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Color.hpp"
#include "RectangleMap.h"
#include "visibilitypolygon.h"

typedef sf::Vector2i Pointi;


namespace light
{

	extern std::vector<sf::Vertex> lightMap;
	extern sf::VertexArray lightTiles;
	//extern std::map<Pointi,bool> lights;
	extern  RectangleMap*  Map;
	extern sf::Texture lightTexture;
	extern Triangles lightPolygon;
	extern vector<Triangles> lightPolygons;
	extern sf::BlendMode additiveBlending;
	

	
	void turnOn(Pointi& light);
	void init( RectangleMap* const map_);
	void updateTiles();

}