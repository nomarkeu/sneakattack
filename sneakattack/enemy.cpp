#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <fstream>
#include <exception>
#include <iostream>
#include "utilities.h"

Enemy::Enemy(): Character(50.0), isAlive(true), Map("mapfile")
{


	turning = false;
	turningSpeed = 90.f; //degrees per second;
	heading = 0.f;
	targetHeading = 0.f;
	attackRange = 25.0f;
	sprite.setSize(Point(10, 10));
	sf::FloatRect boundingBox = sprite.getLocalBounds();
	sprite.setOrigin(boundingBox.width / 2.f, boundingBox.height / 2.f);
	sprite.setFillColor(sf::Color::Red);
	try { setPath(); }
	catch (const std::exception& e) { std::cout << e.what(); }
	location = enemy_path[0];
	pointAhead = ++enemy_path.begin();
	viewcone.setPointCount(3);
	viewcone.setFillColor(sf::Color(161, 207, 223,100));
	setViewcone();
	takeAStep(.01f);
	heading = targetHeading;
	update();
}

void Enemy::setPath()
{
	std::ifstream pathFile("enemyPath");
//	double line;
	Point point;
	char comma;
	if (pathFile.is_open()) 
		while (pathFile>>point.x>>comma>>point.y)
			enemy_path.push_back(point);	
	else throw std::runtime_error("Could not open file enemyPath");	
	if (enemy_path.size() < 2) throw std::runtime_error("not enough points in file enemyPath");
}

void Enemy::move(const float& dtAsSeconds=0.05f)
{
	if (turning) turn(dtAsSeconds);
	else tryAStep(dtAsSeconds);
	update();
}

void Enemy::tryAStep(const float& dtAsSeconds)
{	
	float dS = speed*dtAsSeconds;
	if (dS < distanceToPointAhead()) takeAStep(dtAsSeconds);		
	else {
		dS -= distanceToPointAhead();
		location = *pointAhead;
		if (++pointAhead == enemy_path.end()) pointAhead = enemy_path.begin();			
		tryAStep(dtAsSeconds);
		turning = true;
		turn(dtAsSeconds);
	}	
}

void Enemy::takeAStep(const float& dtAsSeconds)
{
	float dS = speed*dtAsSeconds;
	float ratio = dS / distanceToPointAhead();
	float dx = pointAhead->x - location.x;
	float dy = pointAhead->y - location.y;
	Point newLocation((location.x)+dx*ratio,(location.y)+dy*ratio);
	location = newLocation;
	targetHeading = 180.0f*std::atan2(-dx, dy) / 3.14f;
	if (signbit(targetHeading - heading)) turnDirection = -1;
	else turnDirection = 1;
}

const bool& Enemy::defend(const Point& playerLocation)
{
	if (attackRange > utility::findDistance(playerLocation, getLocation())) isAlive = false;
	return !isAlive;
}

void Enemy::setViewcone()
{
	viewcone.setOrigin(location);
	viewcone.setPosition(location);
	viewcone.setPoint(0, location);
	viewcone.setPoint(1, location - Point(200.f, -500.f));
	viewcone.setPoint(2, location + Point(200.f, 500.f));
	viewcone.setRotation(heading);	
}

void Enemy::update()
{
	setViewcone();
	sprite.setPosition(Point(location.x, location.y));
}


bool Enemy::sense(const Point& player)
{

	Point a = viewcone.getPoint(0);
	Point b = viewcone.getPoint(1);
	Point c = viewcone.getPoint(2);
	sf::Transform tr=viewcone.getTransform();
	a=tr.transformPoint(a);
	b = tr.transformPoint(b);
	c = tr.transformPoint(c);
	return pointInTriangle(player, a, b, c) && lineOfSight(player);
}

void Enemy::turn(const float& elapsedTime)
{
	heading += turnDirection*turningSpeed*elapsedTime;
	if (abs(heading - targetHeading)<turningSpeed*elapsedTime) {
		heading = targetHeading;
		turning = false;
	}
}

bool Enemy::lineOfSight(const Point& player)
{
	Segment los{ location,player };

	for (const auto& segment : Map.getLineSegments())
		if (whichside(segment[0], los) != whichside(segment[1], los))
			if(whichside(player,segment) != whichside(location,segment))
				return false;

	return true;
}


