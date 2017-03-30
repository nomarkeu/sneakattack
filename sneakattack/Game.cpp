#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game() : gameState(State::running), Map("mapfile")
{
	//map.setMap("map");

	if (!texture.loadFromFile("floor.png"))
		throw std::runtime_error("Could not load file player.png");
	
	texture.setRepeated(true);
	background.setTexture(texture);
	background.setTextureRect(sf::IntRect(0, 0, 800, 600));

	Point resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y =  sf::VideoMode::getDesktopMode().height;

	window.create(sf::VideoMode(resolution.x, resolution.y),
		"Sneak Attack");//,
		//sf::Style::);


	pressedKeys[key::W] = false;
	pressedKeys[key::S] = false;
	pressedKeys[key::A] = false;
	pressedKeys[key::D] = false;
	pressedKeys[key::LShift] = false;
	pressedKeys[key::leftClick] = false;
		
}


void Game::start()
{
	sf::Clock clock;

	while (window.isOpen())
	{
		// Restart the clock and save the elapsed time into dt
		sf::Time dt = clock.restart();

		// Make a fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		input();
		update(dtAsSeconds);

		if (gameState == State::running)
			draw();
		else {
			gameOver();
			return;
		}
	}

}

void Game::gameOver()
{

	if (gameState == State::killed) {
		std::cout << " You won" << std::endl;
		window.close();
	}
	else if (gameState == State::spotted) {
	std::cout << " You were spotted!" << std::endl;
	window.close();
	}

}

bool Game::thereIsInput()
{
	return pressedKeys[key::W] || pressedKeys[key::A] || pressedKeys[key::S] || pressedKeys[key::D];
}