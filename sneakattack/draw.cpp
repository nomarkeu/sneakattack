#include "stdafx.h"
#include "Game.h"
#include "lightmap.h"

void Game::draw()
{
	window.clear(sf::Color::Black);
	window.draw(background);
	
	renderTexture.clear();

	renderTexture.draw(foreground);
	renderTexture.draw(enemy.getViewcone());
	renderTexture.draw(enemy.getSprite());
	renderTexture.draw(player.getSprite());
	renderTexture.draw(light::lightTiles);
	
	renderTexture.display();

	window.draw(player.getVisibilityPolygon());

	window.display();
}	