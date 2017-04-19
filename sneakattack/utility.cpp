#include "stdafx.h"
#include "utility.h"
#include <SFML/Graphics.hpp>

float utility::findDistance(const Point& pointA, const Point& pointB)
{
	return std::sqrt(std::pow(pointB.y - pointA.y, 2.0f) + std::pow(pointB.x - pointA.x, 2.0f));
}

bool pointInTriangle(Point s, Point a, Point b, Point c)
{
	float as_x = s.x - a.x;
	float as_y = s.y - a.y;
	bool s_ab = (b.x - a.x)*as_y - (b.y - a.y)*as_x > 0.0f;

	if ((c.x - a.x)*as_y - (c.y - a.y)*as_x > 0.0f == s_ab) return false;
	if ((c.x - b.x)*(s.y - b.y) - (c.y - b.y)*(s.x - b.x) > 0.0f != s_ab) return false;

	return true;
}