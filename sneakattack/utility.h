#pragma once
#include <SFML/Graphics.hpp>

typedef sf::Vector2f Point;
typedef std::vector<sf::Sprite&> Visuals;

namespace utility
{
	float findDistance(const Point&, const Point&);
}

enum class key { W, S, A, D, LShift, leftClick };

bool pointInTriangle(Point s, Point a, Point b, Point c);

