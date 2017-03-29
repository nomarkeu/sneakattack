#pragma once
#include "utilities.h"
#include <array>
class RectangleMap : public sf::Drawable, public sf::Transformable
{
public:

	void append(const sf::Vertex* line)
	{
		for (int i = 0; i != 2; i++)
			lines.append(line[i]);
		// throw an exception if size not 4
	}

	RectangleMap() {
		lines.setPrimitiveType(sf::Lines);
}
	RectangleMap(const vector<Segment>& linesegments)
	{  
		lines.setPrimitiveType(sf::Lines);
		for (const auto& linesegment : linesegments) {
			sf::VertexArray mapLine(sf::Lines,2);
			sf::Vertex* vertex = &mapLine[0];
			vertex[0].position = linesegment[0];
			vertex[1].position = linesegment[1];
			vertex[0].color = vertex[1].color= sf::Color::Black;

			

			append(vertex);
			



		}

		

	}

	
private:

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		// apply the transform
		states.transform *= getTransform();

		// apply the tileset texture
		states.texture = NULL;

		// draw the vertex array
		target.draw(lines, states);


	}

	sf::VertexArray lines;

};
