#pragma once
#include <SFML/Graphics.hpp>
#include "utility.h"
#include "visibilitypolygon.h"
//#include "visibility.h"
#include "RectangleMap.h"
#include <unordered_set>


class Character {
public:
	 const sf::RectangleShape& getSprite() const { return sprite; }
	Character(float s) : speed(s) {}
	
protected:
	Point location;
	sf::Texture texture;
	sf::RectangleShape sprite;
	float speed;
	float heading;

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
	const bool sense(const Point&);
	const bool isPlayerInLOS() const { return playerInLOS; }
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
	RectangleMap Map;
	enum class AlertState {NORMAL, ALERT}; // stay alert for as long as the player is in the viewcone. If player is in view cone for >2s, detect
	AlertState alertState;
	const float alertDelay;
	float alertDuration; // time for which player has been in continuous detection
	bool playerInLOS; // whether enemy is in LOS of player, to show viewcone only when player can see enemy in Game::draw()

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


	bool lineOfSight(const Point& player);
	
	void update();
};




class Player : public Character {
	
public:
	
	Player(sf::RenderTexture& rendertexture);

	void move( std::map<key, bool>&, const float&, const Point&);
	const bool& attack(Enemy& enemy) const { return enemy.defend(this->getLocation()); }
	const Point& getLocation() const { return location; }
	const Triangles& getVisibilityPolygon() const { return visibilityPolygon; }

private:

	Player();

	Triangles visibilityPolygon;
	float runSpeed;
	RectangleMap Map;
	std::array<int, 9> gridTiles;
	int wallTilecount;
	std::vector<int> level;
	mutable std::vector<int> wallTilesNearby;

	void updategridTiles();
	void update();
	bool potentialCollision() const;
	void collide() ;
	
};
