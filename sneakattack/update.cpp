#include "stdafx.h"
#include "Game.h"

 void Game::update(float dtAsSeconds)
{
	 if(thereIsInput())
		 player.move(pressedKeys, dtAsSeconds);

	// if (pressedKeys[key::leftClick])
		 //if (player.attack(enemy))
			// gameState = State::killed;
	 
	// if (enemy.sense(player.getLocation()))
	//	 gameState = State::spotted;


	 //enemy.move(dtAsSeconds);
}