#pragma once
#include "SFML\Graphics.hpp"

class Triangles : public sf::Drawable, public sf::Transformable
{
public:

	void append(const sf::Vertex* triangle)
	{
		for(int i=0;i!=3;i++)
			triangles.append(triangle[i]);
	}
	
	Triangles() {
		triangles.setPrimitiveType(sf::Triangles);
		
	}

	sf::VertexArray triangles;
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = NULL;

		// draw the vertex array
		target.draw(triangles, states);
		
		
	}


	
};
