#pragma once
#include "SFML\Graphics.hpp"
#include "utilities.h"

class Triangles : public sf::Drawable, public sf::Transformable
{
public:
	Triangles(const sf::Texture& rendertexture) : texture(rendertexture)
	{
		triangles.setPrimitiveType(sf::Triangles);
	}

	void tieUpTheEnds(const Point& observer)
	{
		if (isrightturn(triangles[1].position, observer, triangles[triangles.getVertexCount() - 1].position))
			triangles[triangles.getVertexCount()-1] = triangles[1];
	}

	const Point begin() const {	return triangles[1].position; }
	void clear() { triangles.clear(); }
	void append(const sf::Vertex* triangle)
	{
		for(int i=0;i!=3;i++)
			triangles.append(triangle[i]);
	}
	
	void setTexture()
	{
		int size = triangles.getVertexCount();
		for (int i = 0; i < size; i++) {
			triangles[i].texCoords = triangles[i].position;
		}
	}

	void setLightTexture(int x, int y)
	{
		int size = triangles.getVertexCount();
		for (int i = 0; i < size; i++) {
			triangles[i].texCoords = triangles[i].position + Point(640-x,480-y);
		}
	}

	const size_t getVertexCount() const { return triangles.getVertexCount(); }
	const sf::Vertex& operator[](size_t index) const { return triangles[index]; }	

private:
	void operator=(Triangles&) {}; // no assignment allowed
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = &texture;

		// draw the vertex array
		target.draw(triangles, states);
		
		
	}

	sf::VertexArray triangles;
	const sf::Texture& texture;
};
