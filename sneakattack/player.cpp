#include "stdafx.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <map>
#include "SATCollision.h"
#include "visibility.h"



Player::Player(sf::RenderTexture& rendertexture) : visibilityPolygon(rendertexture.getTexture()), Character(50.0f), runSpeed(2*speed), Map("mapfile"), wallTilecount(15)
{
	
	
	level = { 1,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2,3,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,12,2,2,2,2,2,10,16,16,6,2,2,2,2,2,8,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,9,10,16,16,6,2,2,2,2,2,2,2,8,
		5,16,16,16,16,16,16,16,16,16,16,16,11,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		12,2,2,2,2,2,2,2,2,2,2,2,3,16,16,16,16,16,16,16,16,16,16,16,16,16,16,1,2,2,2,2,2,2,10,16,16,6,2,8,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		12,2,2,2,2,2,2,2,2,2,2,2,7,16,16,16,16,16,16,16,16,16,16,16,16,16,16,12,10,16,16,6,2,2,2,2,2,2,2,8,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		9,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,14,2,2,2,2,2,2,2,2,2,2,2,7 };

	if (!texture.loadFromFile("player.png")) throw std::runtime_error("Could not load file player.png");
	sprite.setSize(Point(18, 48));
	
	sprite.setTexture(&texture);
	sprite.setTextureRect(sf::IntRect(9, 8, 18, 48));
	//sprite.setRadius(25.0f);
	sf::FloatRect boundingBox = sprite.getLocalBounds();
	sprite.setOrigin(boundingBox.width / 2.f, boundingBox.height / 2.f);
	location = Point(636.f, 153.f) ;
	update();
}
//
void Player::move(std::map<key, bool>&  pressedKeys,const float& dtAsSeconds, const Point& mousepoint)
{
	int vertical = pressedKeys[key::W] - pressedKeys[key::S];
	int horizontal = pressedKeys[key::D] - pressedKeys[key::A];
	float pace;

	if (pressedKeys[key::LShift]) pace = runSpeed;
	else pace = speed;

	float dx = horizontal*pace*dtAsSeconds;
	float dy = -vertical*pace*dtAsSeconds;
	int sideways = abs(vertical + horizontal);
	if (sideways == 0 || sideways == 2) {
		dx /= sqrt(2.0f);
		dy /= sqrt(2.0f);
	}
	location.x += dx;
	location.y += dy;

	float angledy = mousepoint.y - location.y;
	float angledx = mousepoint.x - location.x;

	//if(dx || dy) 

//	float previousRotation = sprite.getRotation();

	sprite.setRotation(180.0f*std::atan2(angledy, angledx)/3.14f);


	updategridTiles();

	update();

	if (potentialCollision())
		collide();


//	sf::Transform transform = sprite.getTransform();
	
	

	//std::cout << transform.transformPoint(sprite.getPoint(0)).x << std::endl;

	//updategridTiles();

	


}

void Player::update()
{
	sprite.setPosition(Point(int(location.x), int(location.y)));
	visibilityPolygon.clear();
	visibility( Map.getLineSegments(), Map.getAllPoints(),location, visibilityPolygon);
	visibilityPolygon.setTexture();
}

void Player::updategridTiles()
{
	int centreTile = static_cast<int>(location.x / 32.0f) + static_cast<int>(location.y / 32) * 40;

	gridTiles[0] = centreTile - 41;
	gridTiles[1] = centreTile - 40;
	gridTiles[2] = centreTile - 39;
	gridTiles[3] = centreTile - 1;
	gridTiles[4] = centreTile;
	gridTiles[5] = centreTile + 1;
	gridTiles[6] = centreTile + 39;
	gridTiles[7] = centreTile + 40;
	gridTiles[8] = centreTile + 41;

}

bool Player::potentialCollision() const
{
	wallTilesNearby.clear();

	for (auto& tile : gridTiles)
		if (level[tile] < (wallTilecount + 1)) 
			wallTilesNearby.push_back(tile);
	
	return !wallTilesNearby.empty();
}

void Player::collide() 
{
	float left, top;
	Vector projectionVector;

	std::array<Point, 4> wallRect, playerRect;

	sf::Transform transform = sprite.getTransform();

	for (int count = 0; count != 4; count++)
		playerRect[count] = transform.transformPoint(sprite.getPoint(count));
		
	for (auto& tile : wallTilesNearby) {
		left = (tile % 40)*32;
		top = (tile / 40)*32;

		wallRect[0] = Point(left, top);
		wallRect[1] = Point(left + 32.f, top);
		wallRect[3] = Point(left, top + 32.f);
		wallRect[2] = Point(left + 32.f, top + 32.f);	

		if (SATCollision(wallRect, playerRect, projectionVector))
			location += projectionVector;
		}


	update();

	}
	
	