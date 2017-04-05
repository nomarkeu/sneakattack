#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "tilemap.h"




class Game {
public:
	Game();
	void start();
	
private:
	enum class State { running, spotted, killed };
	State gameState;
	sf::Texture texture;
	TileMap background;
	sf::RenderWindow window;
	std::map<key, bool> pressedKeys;


	RectangleMap Map;


	Player player;
	Enemy enemy;

	void readTileMap();
	bool thereIsInput();
	void gameOver();
	void input();
	void update(sf::Clock&);
	void draw();
};
