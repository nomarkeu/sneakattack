#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"





class Game {
public:
	Game();
	void start();
	
private:
	enum class State { running, spotted, killed };
	State gameState;
	sf::Texture texture;
	sf::Sprite background;
	sf::RenderWindow window;
	std::map<key, bool> pressedKeys;


	RectangleMap Map;


	Player player;
	Enemy enemy;

	bool thereIsInput();
	void gameOver();
	void input();
	void update(sf::Clock&);
	void draw();
};
