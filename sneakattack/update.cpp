#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include <iomanip>

 void Game::update(float dtAsSeconds)
{
	 if (thereIsInput()) {
		 player.move(pressedKeys, dtAsSeconds);
		 std::streamsize prec = std::cout.precision();
		 std::cout << std::setprecision(8) <<player.getLocation().x << "," << player.getLocation().y << std::endl << "------" << std::setprecision(prec) << std::endl;
	 }
	 

	// if (pressedKeys[key::leftClick])
		 //if (player.attack(enemy))
			// gameState = State::killed;
	 
	// if (enemy.sense(player.getLocation()))
	//	 gameState = State::spotted;


	 //enemy.move(dtAsSeconds);
}