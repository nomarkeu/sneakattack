#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <array>
#include <utility>
#include "RectangleMap.h"	
#include <unordered_set>

RectangleMap::RectangleMap(const std::string& mapfile)
{
	mapreader2(mapfile);
	lines.setPrimitiveType(sf::Lines);
	for (const auto& linesegment : linesegments) {
		sf::VertexArray mapLine(sf::Lines, 2);
		sf::Vertex* vertex = &mapLine[0];
		vertex[0].position = linesegment[0];
		vertex[1].position = linesegment[1];
		vertex[0].color = vertex[1].color = sf::Color::Black;
		append(vertex);
	}
}

void RectangleMap::mapreader(const std::string& mapfile)
{
	linesegments.clear();
	std::ifstream Map_(mapfile);
	if (Map_.is_open()) {
		Segment segment;
		std::array<sf::Vector2f, 4> points;
		char delimiter;
		int totalPointCounter = 0;
		while (Map_ >> points[0].x >> delimiter >> points[0].y >> delimiter) {
			for (int i = 1; i != 4; i++)
				Map_ >> points[i].x >> delimiter >> points[i].y >> delimiter;
			for (int i = 0; i != 3; i++) {
				allpoints.push_back(std::make_pair(totalPointCounter++, points[i]));
				segment = { points[i],points[i + 1] };
				linesegments.push_back(segment);
			}
			segment = { points[3], points[0] };
			allpoints.push_back(std::make_pair(totalPointCounter++, points[3]));
			linesegments.push_back(segment);
		}
	}
}

void RectangleMap::mapreader2(const std::string& mapfile)
{

	auto equal = [](const Pointmap pt1, const Pointmap pt2) {
		return pt1.second==pt2.second;
	};

	auto hash = [](const Pointmap& pt) {
		return (size_t)(pt.second.x * 100 + pt.second.y);
	};

	using Pointhash = std::unordered_set < Pointmap, decltype(hash), decltype(equal) >;
	Pointhash allpoints_set(10,hash,equal);

	linesegments.clear();
	std::ifstream Map_(mapfile);
	if (Map_.is_open()) {
		Segment segment;
		std::array<sf::Vector2f, 2> points;
		char delimiter;
		int totalPointCounter = 0;
		while (Map_ >> points[0].x >> delimiter >> points[0].y >> delimiter) {
				Map_ >> points[1].x >> delimiter >> points[1].y >> delimiter;
				segment = { points[0],points[1] };
				linesegments.push_back(segment);
				allpoints_set.insert(std::make_pair(totalPointCounter++, points[0]));		
		}
	}
	std::copy(allpoints_set.begin(), allpoints_set.end(), std::back_inserter(allpoints));
}

void RectangleMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if(allpoints.empty())
		throw std::runtime_error("no points in map (did you initialize with a mapfile?)");
	// apply the transform
	states.transform *= getTransform();
	// apply the tileset texture
	states.texture = NULL;
	// draw the vertex array
	target.draw(lines, states);
}

void RectangleMap::append(const sf::Vertex* line)
{
	for (int i = 0; i != 2; i++)
		lines.append(line[i]); // throw an exception if size not 4
}