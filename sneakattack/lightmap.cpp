#include "stdafx.h"
#include "lightmap.h"
#include "visibility.h"
#include "utility.h"



namespace light
{
	 std::vector<sf::Vertex> lightMap(1271);
	 sf::VertexArray lightTiles(sf::Quads,4800);
	// std::map<Pointi, bool> lights;
	  RectangleMap*  Map;
	  sf::Texture lightTexture;
	  Triangles lightPolygon(lightTexture);
	 vector<Triangles> lightPolygons;// (10, Triangles(lightTexture));
	 sf::BlendMode additiveBlending = sf::BlendAdd;



	 void init( RectangleMap* const map_) {
		

		 lightTexture.loadFromFile("lightmap.png");
	
		 Map = map_;

		int vertexcount = 0;// static_cast<int>(lightMap.size());

		for (auto& vertex : lightMap) {
			vertex.color = sf::Color::Black;
			vertex.color.a = 200;
		
			vertex.position.x = (vertexcount % 41) * 32;
			vertex.position.y = (vertexcount / 41) * 32;
			vertexcount++;
		}
		
	//	lightMap[100].color.a = 0;

		//int mCount = static_cast<int>(lightMap.size());
		

		turnOn(Pointi(600, 33));
		turnOn(Pointi(600, 600));
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

		 Point p0 = lightPolygon[0].position; // this point is always same for all triangles, ie the light's position
		 Point p1, p2;
		 sf::Uint32 alpha;

		 for (int count = 0; count != size; count += 3) {

			 p1 = lightPolygon[count + 1].position;
			 p2 = lightPolygon[count + 2].position;

			 xmax = std::max(std::max(p0.x, p1.x), p2.x);
			 xmin = std::min(std::min(p0.x, p1.x), p2.x);
			 ymax = std::max(std::max(p0.y, p1.y), p2.y);
			 ymin = std::min(std::min(p0.y, p1.y), p2.y);

			 for (auto& vertex : lightMap)
				 if (pointInTriangle(vertex.position, p0, p1, p2)) {
					 alpha = std::min(50.f,300.f/ ((pow((vertex.position - p0).x/128.f, 2.f) + pow((vertex.position - p0).y/128.f, 2.f))));
					 vertex.color = sf::Color(244, 206, 66, alpha);
				 }

			 

			  xmax = 0;
			  xmin = std::numeric_limits<float>::max();
			  ymax = 0;
			  ymin = xmin;

		 }

		 //lightPolygon.setLightTexture(light.x,light.y);
		 //lightPolygons.push_back(lightPolygon);
		 
	 }

	 void updateTiles()
	 {
		 int tCount = static_cast<int>(lightTiles.getVertexCount()) / 4;

		 for (size_t count = 0; count != tCount; count++) {
			 lightTiles[count * 4] = lightMap[count + count / 40];
			 lightTiles[count * 4 + 1] = lightMap[count + count / 40 + 1];
			 lightTiles[count * 4 + 2] = lightMap[count + count / 40 + 42];
			 lightTiles[count * 4 + 3] = lightMap[count + count / 40 + 41];
		 }
	 }

}