#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

 void Game::update(sf::Clock& clock)
{
	 input();

	 sf::Time dt = clock.restart();
	 float dtAsSeconds = dt.asSeconds();

	// if (thereIsInput()) {
		 player.move(pressedKeys, dtAsSeconds, window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		// std::streamsize prec = std::cout.precision();
		// std::cout << std::setprecision(8) <<player.getLocation().x << "," << player.getLocation().y << std::endl << "------" << std::setprecision(prec) << std::endl;
	// }
	 

	// if (pressedKeys[key::leftClick])
		 //if (player.attack(enemy))
			// gameState = State::killed;
	 
	// if (enemy.sense(player.getLocation()))
		// gameState = State::spotted;


	 enemy.move(dtAsSeconds);
}