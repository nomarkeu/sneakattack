#include "stdafx.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <map>



Player::Player() : Character(200.0), runSpeed(2*speed), Map("mapfile")
{
	
	if (!texture.loadFromFile("player.png")) throw std::runtime_error("Could not load file player.png");
	sprite.setTexture(&texture);
	sprite.setRadius(50.0);
	sf::FloatRect boundingBox = sprite.getLocalBounds();
	sprite.setOrigin(boundingBox.width / 2, boundingBox.height / 2);
	location = Point(700.0,500.0) ;
	update();
}
//
void Player::move( std::map<key, bool>&  pressedKeys,const float& dtAsSeconds)
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
		dx /= sqrt(2);
		dy /= sqrt(2);
	}
	location.x += dx;
	location.y += dy;
	if(dx || dy) sprite.setRotation(180.0*std::atan2(dy,dx)/3.14);
	update();
}

void Player::update()
{
	sprite.setPosition(Point(location.x, location.y));
	visibility( Map.getLineSegments(), Map.getAllPoints());
}