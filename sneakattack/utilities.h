#pragma once
#include "SFML\Graphics.hpp"
#include <assert.h>
#include <array>
using std::array;
using std::vector;
typedef std::array<sf::Vector2f, 2> Segment;
typedef sf::Vector2f Point;
typedef std::pair<int, Point> Pointmap;
typedef Point Vector;
#define pi 3.14159265358f

void mapreader(vector<Segment>& linesegments, vector<Pointmap>& allpoints);

inline bool approx_equal(const float& a, const float& b,  float epsilon = std::numeric_limits<float>::epsilon())
{
	epsilon = .01f;
	return std::abs(a - b) <= std::max(std::abs(a), std::abs(b)) * epsilon;
}

inline bool approx_equal(const Point& a, const Point& b)
{
	return approx_equal(a.x, b.x) && approx_equal(a.y, b.y);
}

inline bool approx_equal(const Segment& a, const Segment& b)
{
	bool returnvalue = approx_equal(a[0], b[0]) && approx_equal(a[1], b[1])
		|| approx_equal(a[0], b[1]) && approx_equal(a[1], b[0]);
	return returnvalue;
}

inline int whichside(const Point p, const Segment& s)
{
	Point a = s[0], b = s[1];
	float side = (b.y - a.y)*(p.x - a.x) - (p.y - a.y)*(b.x - a.x);
	if (abs(side)< 0.01f) return 0;
	if (side < 0.0f) return -1;
	if (side > 0.0f) return 1;
	
}

inline int whichside2(const Point p, const Segment& s)
{
	Point a = s[0], b = s[1];
	float side = (b.y - a.y)*(p.x - a.x) - (p.y - a.y)*(b.x - a.x);
	if (abs(side)< 0.01f) return 0;
	if (side < 0.0f) return -1;
	if (side > 0.0f) return 1;
	
}

struct AngleComparator
{
	
	
	AngleComparator(const Point& p) : player(p) {}
	bool operator()(const Pointmap& p1, const Pointmap& p2) const
	{
		float angle = GetAngleABC(p1.second, player, p2.second);
		if (angle < 0.0f) return false;
		if (angle > 0.0f) return true;
		else 
			return false;
		//return p1.second.x < p2.second.x;
		//return angle;
	}

private:
	Point player;
	float GetAngleABC(const Point& a, const Point& b, const Point& c) const
	{
		Vector ab = { b.x - a.x, b.y - a.y };
		Vector cb = { b.x - c.x, b.y - c.y };

		float dot = (ab.x * b.x + ab.y * b.y); // dot product
		float cross = (ab.x * b.y - ab.y * b.x); // cross product

		float alpha1 = atan2(cross, dot);
		alpha1 = alpha1 < 0.0f ? 2.0f * pi + alpha1 : alpha1;


		 dot = (b.x * cb.x + b.y * cb.y); // dot product
		 cross = ( b.y * cb.x - b.x * cb.y); // cross product

		float alpha2 = atan2(cross, dot);
		alpha2 = alpha2 < 0.0f ? 2.0f * pi + alpha2 : alpha2;

		return ((alpha1-alpha2) * 180.0f / pi)*100.0f;
	};


};

struct lineSegmentCompare
{
	

	lineSegmentCompare(const Point& p) : player(p) {}

	bool operator()(const Segment& s1, const Segment& s2) const
	{
		Point a1 = s1[0]; Point b1 = s1[1];
		Point a2 = s2[0]; Point b2 = s2[1];

		// if no common points
		int playerside2 = whichside(player, s2);
		int a1side = whichside(a1, s2);
		int b1side = whichside(b1, s2);
		if (playerside2 == a1side && playerside2 == b1side) return true;

		int playerside1 = whichside(player, s1);
		int a2side = whichside(a2, s1);
		int b2side = whichside(b2, s1);

		if (a2side == b2side && playerside1 == -a2side)
			return true;

		if (playerside1 == a2side && playerside1 == b2side) return false;

		if (a1side == b1side && playerside2 == -a1side)
			return false;

		//if common points
		bool a1a2 = approx_equal(a1, a2);
		bool a1b2 = approx_equal(a1, b2);
		bool b1a2 = approx_equal(b1, a2);
		bool b1b2 = approx_equal(b1, b2);

		if (a1a2 || a1b2) {
			if (whichside(a2, Segment{ a1,player }) != whichside(b1, Segment{ a1,player }))
				if(a1a2)
					return (b1.x > b2.x) ? true : false;
				else
					return (b1.x>a2.x) ? true : false;
			
			return playerside2 == b1side;
		}
		else if (b1a2 || b1b2) {
			if (whichside(b2, Segment{ b1,player }) != whichside(a1, Segment{ b1,player }))
				if(b1a2)
					return (a1.x > b2.x) ? true : false;
				else
					return (a1.x > a2.x) ? true : false;

			return playerside2 == a1side;
		}

		//if collinear
	}

private:
	Point player;


};


inline Point intersection(const Segment& segment, const Point& point, const Point& observer)
{   
	float dx = observer.x - point.x;
	float dy = observer.y - point.y;
	assert(dx != 0.0f);
	float m1 = dy / dx;

	dx = segment[1].x - segment[0].x;
	dy = segment[1].y - segment[0].y;
	//assert(dx != 0);
	float m2 = dy / dx;
	// y = mx + c
	// intercept c = y - mx
	float intersection_X;
	float intersection_Y;
	float c1;
	float c2;

	if (isinf(m2)) {
		c1 = observer.y - m1 * observer.x;
		intersection_X = segment[1].x;
		intersection_Y = m1 * intersection_X + c1;
	}
	else if (isinf(m1)) {
		c2 = segment[1].y - m2 * segment[1].x;
		intersection_X = point.x;
		intersection_Y = m2 * intersection_X + c2;
	}
	else {
		 c1 = observer.y - m1 * observer.x; 

		 c2 = segment[1].y - m2 * segment[1].x; 

		assert((m1 - m2) != 0.0f);
		 intersection_X = (c2 - c1) / (m1 - m2);
		 intersection_Y = m1 * intersection_X + c1;
	}

		return Point{ intersection_X,intersection_Y };
	

}


inline bool intersecting(const Segment& segment, const Point& point, const Point& observer)
{
	int first = whichside2(segment[0], Segment{ point,observer });
	int second = whichside2(segment[1], Segment{ point,observer });
	
	bool intersecting = false;

	if (first == -second) intersecting = true;
	if (first == 0 || second == 0) intersecting = true;
	
	if (intersecting) {	// x3,y3						 x1,y1  x2,y2
		Point intersecting_point = intersection(segment, point, observer);
		
		if (point.x < observer.x && ((intersecting_point.x < observer.x) || approx_equal(intersecting_point,point)))
			return true;
		else if (point.x > observer.x && ((intersecting_point.x > observer.x) || approx_equal(intersecting_point, point)))
			return true;
		else if (approx_equal(intersecting_point, point))
			return true;
	}

	
	return false;

}

//checks if c is right of the vector  ba
inline bool isrightturn(const Point& a, const Point& b, const Point& c) 
{
	Vector ba = { a.x - b.x,a.y - b.y };
	Vector bc = { c.x - b.x, c.y - b.y };

	//crossproduct = cross(ba, bc); or ba x bc

	float crossproduct = ba.x*bc.y - ba.y*bc.x;

		if (crossproduct > 0.0f && !approx_equal(crossproduct/1000000000000.0f,0.0))
			return true;		//is right turn
		/*else if (crossproduct>0)
			left turn;
		else if (approx equal 0)
			colliniar*/

	return false;
}


inline bool coincidentLeftTurn(const Segment& segment,const Point& point, const Point& observer)
{
	
	if ((approx_equal(point, segment[0]))) {
		return !isrightturn(point, observer, segment[1]);
			
	}
	else if ((approx_equal(point, segment[1])))
	{
		return !isrightturn(point, observer, segment[0]);
	}
		

	return false;


}