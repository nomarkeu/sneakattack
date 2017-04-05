#pragma once
#include "utilities.h"
#include <array>
#include <map>



class RectangleMap : public sf::Drawable, public sf::Transformable
{
public:
	RectangleMap(){ lines.setPrimitiveType(sf::Lines); }
	
	RectangleMap(const std::string& mapfile);
	const vector<Segment>& getLineSegments() const { return linesegments; }
	 vector<std::pair<int, Point> >& getAllPoints()  { return allpoints; }
	//void setMap(const std::string& mapfile) { RectangleMap(mapfile); };
	
private:
	
	sf::VertexArray lines;
	vector<Segment> linesegments;
	vector<std::pair<int, Point> > allpoints;
	void mapreader(const std::string& mapfile);
	void mapreader2(const std::string& mapfie);
	void append(const sf::Vertex* line);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
