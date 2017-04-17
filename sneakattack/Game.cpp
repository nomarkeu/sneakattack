#include "stdafx.h"
#include "Game.h"
#include <iostream>
#include "lightmap.h"

Game::Game() : gameState(State::running), Map("mapfile"), actionState(ActionState::NONE), zoomLevel(1.5f), player(renderTexture)
{
	//map.setMap("map");

	light::init(&Map);
	gameView.setSize(Point(1280, 960));
	renderTexture.create(1280, 960);

	readTileMap();

	Point resolution;
	resolution.x = 1280;// sf::VideoMode::getDesktopMode().width;
	resolution.y = 960;  sf::VideoMode::getDesktopMode().height;

	
	//view.zoom(.25f);
	

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
	//window.setFramerateLimit(60);
	window.setVerticalSyncEnabled(true);

	sf::View view;
	view.setCenter(640, 480);
	view.setSize(1280, 960);
	view.zoom(1.5f);
	window.setView(view);

	float zoom = 1.5f;

	sf::Event event;


	while (window.isOpen())
	{
		// Restart the clock and save the elapsed time into dt
	
		window.pollEvent(event);

		viewPortManager(event);

		update(clock);

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
	return pressedKeys[key::W] || pressedKeys[key::A] || pressedKeys[key::S] || pressedKeys[key::D] ;
}

void Game::readTileMap()
{
		// create the window
		//sf::RenderWindow window(sf::VideoMode(640, 480), "Tilemap");


		// define the level with an array of tile indices
		const int level[] =
		{
			1,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2,3,
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
			9,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,14,2,2,2,2,2,2,2,2,2,2,2,7
		};

		// create the tilemap from the level definition
	
		if (!background.load("tileset.png", sf::Vector2u(32, 32), level, 40, 30))
			throw std::runtime_error("couldn't load tileset.png");



		if (!foreground.load("visible.png", sf::Vector2u(32, 32), level, 40, 30))
			throw std::runtime_error("couldn't load visible.png");

		//background.scale(sf::Vector2f(.5f, .5f));


}

void Game::viewPortManager(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::MouseMoved:
	{
		/*Pan Camera*/
		if (actionState == ActionState::PANNING) {
			Point pos = sf::Vector2f(sf::Mouse::getPosition(window) -panningAnchor);
			gameView.move(-1.0f * pos *zoomLevel);
			panningAnchor = sf::Mouse::getPosition(window);
		}
		break;
	}

	case sf::Event::MouseButtonPressed:
	{
		/* Start panning */
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			if (actionState != ActionState::PANNING)
			{
				actionState = ActionState::PANNING;
				panningAnchor = sf::Mouse::getPosition(window);
			}
		}
		break;
	}

	case sf::Event::MouseButtonReleased:
	{
		/* Stop panning */
		if (event.mouseButton.button == sf::Mouse::Middle)
		{
			actionState = ActionState::NONE;
		}
		break;
	}

	/* Zoom the view */
	case sf::Event::MouseWheelMoved:
	{
		if (event.mouseWheel.delta < 0)
		{
			gameView.zoom(1.2f);
			zoomLevel *= 1.2f;
		}
		else
		{
			gameView.zoom(.83333f);
			zoomLevel *= .83333f;
		}
		break;
	}

	default:
		break;
	}


	window.setView(gameView);

	

}