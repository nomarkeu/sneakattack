#include "stdafx.h"
#include "Game.h"

void Game::draw()
{
	window.clear(sf::Color::Black);
	//window.draw(background);
	window.draw(Map);
	
	
	window.draw(enemy.getSprite());
	window.draw(enemy.getViewcone());
	window.draw(player.getVisibilityPolygon());
	window.draw(player.getSprite());


	window.display();
}