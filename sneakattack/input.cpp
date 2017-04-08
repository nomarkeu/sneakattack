#include "stdafx.h"
#include "Game.h"

void Game::input()
{
	// Handle the player quitting
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		window.close();
		return;
	}




	// Handle the player moving
	pressedKeys[key::W] = sf::Keyboard::isKeyPressed(sf::Keyboard::W) ? true : false;
	pressedKeys[key::S] = sf::Keyboard::isKeyPressed(sf::Keyboard::S) ? true : false;
	pressedKeys[key::A] = sf::Keyboard::isKeyPressed(sf::Keyboard::A) ? true : false;
	pressedKeys[key::D] = sf::Keyboard::isKeyPressed(sf::Keyboard::D) ? true : false;
	pressedKeys[key::LShift] = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? true : false;
	pressedKeys[key::leftClick] = sf::Mouse::isButtonPressed(sf::Mouse::Left) ? true : false;

}

