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

	TileMap background;	// black and white map which is shown on the invisible part
	TileMap foreground; // the visible part is based on this
	sf::RenderWindow window;	// for displaying game window
	// all the visible entities are drawn on renderTexture: foreground, lightmap, player, enemy, enemy viewcone.
	// And then visibilty map uses renderTexture.getTexture() for it's texture
	sf::RenderTexture renderTexture; 
	std::map<key, bool> pressedKeys;
	
	// zoom and pan 
	sf::View gameView;
	float zoomLevel;
	sf::Vector2i panningAnchor;

	RectangleMap Map;
	
	Player player;
	std::vector<Enemy> enemies;
	

	void readTileMap();
	bool thereIsInput();
	void gameOver();
	void input();
	void update(sf::Clock&);
	void draw();
	void viewPortManager(sf::Event&);
};
