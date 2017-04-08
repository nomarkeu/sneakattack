#include "stdafx.h"
#include "Game.h"

void Game::draw()
{
	window.clear(sf::Color::White);
	window.draw(background);
	
	renderTexture.clear();

	renderTexture.draw(foreground);
	renderTexture.draw(enemy.getViewcone());
	renderTexture.draw(enemy.getSprite());
	
	renderTexture.display();


	window.draw(player.getVisibilityPolygon());

	//::Sprite stuff(renderTexture.getTexture());

	//ndow.draw(stuff);


//	window.draw(Map);
	window.draw(player.getSprite());

	//window.draw(enemy.getSprite());


	window.display();
}	