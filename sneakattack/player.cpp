#include "stdafx.h"
#include "Character.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <exception>
#include <map>



Player::Player() : Character(200.0f), runSpeed(2*speed), Map("mapfile")
{
	
	if (!texture.loadFromFile("player.png")) throw std::runtime_error("Could not load file player.png");
	sprite.setTexture(&texture);
	sprite.setRadius(25.0f);
	sf::FloatRect boundingBox = sprite.getLocalBounds();
	sprite.setOrigin(boundingBox.width / 2.f, boundingBox.height / 2.f);
	location = Point(444.025f, 257.821f) ;
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
		dx /= sqrt(2.0f);
		dy /= sqrt(2.0f);
	}
	location.x += dx;
	location.y += dy;
	if(dx || dy) sprite.setRotation(180.0f*std::atan2(dy,dx)/3.14f);
	update();
}

void Player::update()
{
	sprite.setPosition(Point(int(location.x), int(location.y)));
	visibilityPolygon.clear();
	visibility( Map.getLineSegments(), Map.getAllPoints());
	visibilityPolygon.setTexture();
}