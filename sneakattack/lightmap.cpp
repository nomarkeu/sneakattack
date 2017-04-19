#include "stdafx.h"
#include "lightmap.h"
#include "visibility.h"
#include "utility.h"



namespace light
{
	 std::vector<sf::Vertex> lightMap(19481); // old 40 30 
	 sf::VertexArray lightTiles(sf::Quads,76800); // 160 120
	  RectangleMap*  Map;
	  sf::Texture texture;
	  Triangles lightPolygon(texture);

	 void init( RectangleMap* const map_) {		
		
		 Map = map_;
		int vertexcount = 0;

		for (auto& vertex : lightMap) {
			vertex.color = sf::Color::Black;
			vertex.color.a = 200;		
			vertex.position.x = (vertexcount % 161) * 8;
			vertex.position.y = (vertexcount / 161) * 8;
			vertexcount++;
		}
	
		turnOn(Pointi(600, 33));
		turnOn(Pointi(500, 450));
		updateTiles();	
	}


	 void turnOn(Pointi& light)
	 {
		 lightPolygon.clear();
		 visibility( (*Map).getLineSegments(), (*Map).getAllPoints(), static_cast<Point>(light), lightPolygon);

		 int const size = lightPolygon.getVertexCount();
		 float xmax = 0;
		 float xmin = std::numeric_limits<float>::max();
		 float ymax = 0;
		 float ymin = xmin;
		 float distance = 0;

		 Point p0 = lightPolygon[0].position; // this point is always same for all triangles, ie the light's position
		 Point p1, p2;
		 sf::Uint32 alpha;

		 for (int count = 0; count != size; count += 3) {

			 p1 = lightPolygon[count + 1].position;
			 p2 = lightPolygon[count + 2].position;
			 /*xmax = std::max(std::max(p0.x, p1.x), p2.x);
			 xmin = std::min(std::min(p0.x, p1.x), p2.x);
			 ymax = std::max(std::max(p0.y, p1.y), p2.y);
			 ymin = std::min(std::min(p0.y, p1.y), p2.y);*/
			 for (auto& vertex : lightMap)
				 if (pointInTriangle(vertex.position, p0, p1, p2)) {
					// alpha = std::min(50.f,300.f/ ((pow((vertex.position - p0).x/128.f, 2.f) + pow((vertex.position - p0).y/128.f, 2.f))));
					 distance = sqrt( pow((vertex.position - p0).x, 2.f) + pow((vertex.position - p0).y, 2.f));
					 if (distance < 200.f)
						 vertex.color.a = 0;					 
				 }			 
			/*
			  xmax = 0;
			  xmin = std::numeric_limits<float>::max();
			  ymax = 0;
			  ymin = xmin;
			  */
		 }	
	 }

	 void updateTiles()
	 {
		 int tCount = static_cast<int>(lightTiles.getVertexCount()) / 4;

		 for (size_t count = 0; count != tCount; count++) {
			 lightTiles[count * 4] = lightMap[count + count / 160];
			 lightTiles[count * 4 + 1] = lightMap[count + count / 160 + 1];
			 lightTiles[count * 4 + 2] = lightMap[count + count / 160 + 162];
			 lightTiles[count * 4 + 3] = lightMap[count + count / 160 + 161];
		 }
	 }

}