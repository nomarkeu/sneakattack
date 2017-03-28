#pragma once
#include "SFML\Graphics.hpp"

using std::vector;
typedef std::array<sf::Vector2f, 2> Segment;
typedef sf::Vector2f Point;
typedef std::pair<int, Point> Pointmap;
typedef Point Vector;
typedef std::vector<sf::VertexArray> Triangles;
#define pi 3.1415

void visibility(Triangles& visibilityPolygon, Point observer);
void mapreader(vector<Segment>& linesegments, vector<Pointmap>& allpoints);

inline bool approx_equal(float a, float b, float epsilon = std::numeric_limits<float>::epsilon())
{
	return std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * epsilon;
}

inline bool approx_equal(sf::Vector2f a, sf::Vector2f b)
{
	return approx_equal(a.x, b.x) && approx_equal(a.y, b.y);
}

inline int whichside(const Point p, const Segment& s)
{
	Point a = s[0], b = s[1];
	float side = (b.y - a.y)*(p.x - a.x) - (p.y - a.y)*(b.x - a.x);
	if (side < 0) return -1;
	if (side > 0) return 0;
	if (approx_equal(side, 0.0)) return 0;
}

struct AngleComparator
{
	
	
	AngleComparator(Point p) : player(p) {}
	bool operator()(Pointmap& p1, Pointmap& p2)
	{
		float angle = (GetAngleABC(p1.second, player, p2.second));
		if (angle < 0) return false;
		if (angle > 0) return true;
		else return true;
		//return p1.second.x < p2.second.x;
		//return angle;
	}

private:
	Point player;
	float GetAngleABC(Point a, Point b, Point c)
	{
		Vector ab = { b.x - a.x, b.y - a.y };
		Vector cb = { b.x - c.x, b.y - c.y };

		float dot = (ab.x * b.x + ab.y * b.y); // dot product
		float cross = (ab.x * b.y - ab.y * b.x); // cross product

		float alpha1 = atan2(cross, dot);

		 dot = (b.x * cb.x + b.y * cb.y); // dot product
		 cross = ( b.y * cb.x - b.x * cb.y); // cross product

		float alpha2 = atan2(cross, dot);
		
		return ((alpha1-alpha2) * 180. / pi)*100.0;
	};


};

struct lineSegmentCompare
{
	Point player;

	lineSegmentCompare(Point p) : player(p) {}

	bool operator()(const Segment& s1, const Segment& s2)
	{
		auto a1 = s1[0]; auto b1 = s1[1];
		auto a2 = s2[0]; auto b2 = s2[1];

		// if no common points
		int playerside2 = whichside(player, s2);
		int a1side = whichside(a1, s2);
		int b1side = whichside(b1, s2);
		if (playerside2 == a1side == b1side) return true;

		int playerside1 = whichside(player, s1);
		int a2side = whichside(a2, s1);
		int b2side = whichside(b2, s1);
		if (playerside1 == a2side == b2side) return false;

		//if common points
		if (approx_equal(a1, a2) || approx_equal(a1, b2)) return playerside2 == b1side;
		else if (approx_equal(b1, a2) || approx_equal(b1, b2)) return playerside2 == a1side;

		//if collinear
	}

};


