#pragma once
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "tilemap.h"


enum class ActionState { NONE, PANNING };

class Game {
public:
	Game();
	void start();
	
private:
	enum class State { running, spotted, killed };
	ActionState actionState;
	State gameState;
	//sf::Texture texture;
	TileMap background;
	TileMap foreground;
	sf::RenderWindow window;
	sf::RenderTexture renderTexture;
	std::map<key, bool> pressedKeys;
	sf::View gameView;
	float zoomLevel;
	sf::Vector2i panningAnchor;
	RectangleMap Map;
	
	Player player;
	Enemy enemy;

	void readTileMap();
	bool thereIsInput();
	void gameOver();
	void input();
	void update(sf::Clock&);
	void draw();
	void viewPortManager(sf::Event&);
};
