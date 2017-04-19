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
	//renderTexture.draw(light::lightTiles);s
	//for(auto& light : light::lightPolygons)
	//	renderTexture.draw(light,sf::BlendAdd);
	renderTexture.draw(light::lightTiles);
	
	renderTexture.display();

	//window.draw(light::lightTiles);
	window.draw(player.getVisibilityPolygon());

	//::Sprite stuff(renderTexture.getTexture());

	//ndow.draw(stuff);

	//window.draw(light::lightPolygons[0]);

//	window.draw(Map);
	//window.draw(player.getSprite());

	//window.draw(enemy.getSprite());




	window.display();
}	