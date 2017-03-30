#pragma once
#include <SFML/Graphics.hpp>
#include "utility.h"
#include "visibilitypolygon.h"
//#include "visibility.h"
#include "RectangleMap.h"




class Character {
public:
	virtual const sf::CircleShape& getSprite() const { return sprite; }
	Character(float s) : speed(s) {}
	
protected:
	Point location;
	sf::Texture texture;
	sf::CircleShape sprite;
	float speed;
	float heading;
	//Visuals visuals;


	void move();
	const Point& getLocation() const { return location; }
	void update() { sprite.setPosition(Point(location.x, location.y)); }


};



class Enemy : public Character {
public:
	Enemy();
	void move(const float&);
	const bool alive() const { return isAlive; }
	const bool& defend(const Point&);
	const sf::ConvexShape& getViewcone() const { return viewcone; }
	bool sense(const Point&);
	//void spot(); 

private:
	float turningSpeed;
	float attackRange;
	bool isAlive;
	bool turning;
	float targetHeading;
	int turnDirection;
	std::vector<Point> enemy_path;
	sf::ConvexShape viewcone;

	// pointAhead is always in range [enemy_path.begin(),enemy_path.end())
	// before and after every member function call
	typename std::vector<Point>::iterator pointAhead;
	void turn(const float&);
	void setViewcone();
	void setPath();
	void tryAStep(const float&);
	void takeAStep(const float&);
	float distanceToPointAhead() const
	{
		return utility::findDistance(location, *pointAhead);
	}

	
	void update();
};




class Player : public Character {
	
public:
	Player();
	void move( std::map<key, bool>&, const float&);
	const bool& attack(Enemy& enemy) const { return enemy.defend(this->getLocation()); }
	const Point& getLocation() const { return location; }
	const Triangles& getVisibilityPolygon() const { return visibilityPolygon; }
private:
	void update();
	void visibility(const vector<Segment>& linesegments, vector<Pointmap>& allpoints);
	float runSpeed;
	Triangles visibilityPolygon;
	 RectangleMap Map;
};



//void visibility(Player& player, const vector<Segment>& linesegments, vector<Pointmap>& allpoints);