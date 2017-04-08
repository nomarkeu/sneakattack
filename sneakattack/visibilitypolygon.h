#pragma once
#include "SFML\Graphics.hpp"
#include "utilities.h"

class Triangles : public sf::Drawable, public sf::Transformable
{
public:
	
	void tieUpTheEnds(const Point& observer)
	{
		if (isrightturn(triangles[1].position, observer, triangles[triangles.getVertexCount() - 1].position))
			triangles[triangles.getVertexCount()-1] = triangles[1];
	}

	const Point begin() const
	{
		return triangles[1].position;
	}

	void clear()
	{
		triangles.clear();
	}

	void append(const sf::Vertex* triangle)
	{
		for(int i=0;i!=3;i++)
			triangles.append(triangle[i]);
	}
	
	Triangles(sf::RenderTexture& rendertexture) {
		triangles.setPrimitiveType(sf::Triangles);
		//if (!texture.loadFromFile("visibility.png"))
			//throw std::runtime_error("Couldn't load visibility file");
		texture = &rendertexture;
	}

	void setTexture()
	{
		int size = triangles.getVertexCount();
		for (int i = 0; i < size; i++) {
			triangles[i].texCoords = triangles[i].position;
		}

	}

	
private:
	Triangles() {};

	void operator=(Triangles&) {};
	Triangles(Triangles&) {};

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &texture->getTexture();

		// draw the vertex array
		target.draw(triangles, states);
		
		
	}

	sf::VertexArray triangles;
	const sf::RenderTexture* texture;
	
};
