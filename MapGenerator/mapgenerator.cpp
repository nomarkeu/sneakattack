#include "stdafx.h"
#include "MapGenerator.h"
#include <assert.h>
#include <fstream>

void MapGenerator::start()
{
	sf::Event event;
	window.setFramerateLimit(60);


	sf::View view;
	view.setCenter(640, 480);
	view.setSize(1280, 960);
	window.setView(view);

	while(window.isOpen()){
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
			MapLines.clear();
			i = 0;
			draw = false;
		}



		window.pollEvent(event);
	
		int attachPosition = -1;
		bool attaching = false;

		if (!draw && (event.type == sf::Event::MouseWheelScrolled) && !attaching && (MapLines.getVertexCount() != 0)) {
			attachPosition = attach(Point(event.mouseWheelScroll.x, event.mouseWheelScroll.y));
			attaching = true;
		}

		while (attachPosition != -1) {
			attachPoint = findAttachPoint(window.mapPixelToCoords(sf::Mouse::getPosition(window)), attachPosition);
			attachPointCross[0].position = attachPoint + Vector(-5, 0);
			attachPointCross[1].position = attachPoint + Vector(5, 0);
			attachPointCross[2].position = attachPoint + Vector(0, -5);
			attachPointCross[3].position = attachPoint + Vector(0, 5);

			attaching = false;
			

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

				attachPointCross.clear();
				attachPointCross.resize(4);
				for (int j = 0; j != 4; j++)
					attachPointCross[j].color = sf::Color::Blue;

				newLineSetStart = i;
				MapLines.append(attachPoint);
				MapLines[i].color = sf::Color::Red;
				MapLines.append(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
				MapLines[i+1].color = sf::Color::Red;

				canStartANewLine = false;
				finishing = false;
				lineAttached = true;
				draw = true;
				attachPosition = -1;
				break;
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				attachPointCross.clear();
				attachPointCross.resize(4);
				for (int j = 0; j != 4; j++)
					attachPointCross[j].color = sf::Color::Blue;
				attachPosition = -1;
				break;
				i;
			}


			window.clear(sf::Color::White);
			window.draw(background);
			window.draw(MapLines);
			window.draw(attachPointCross);
			window.display();
		}
		
		drawline();

		window.clear(sf::Color::White);

		window.draw(background);
		window.draw(MapLines);
		window.draw(attachPointCross);
		

		window.display();
	}

	writeToFile();

	window.close();
}

void MapGenerator::drawline()
{
	//int i = vertexnumber;
	/*bool leftClick = false;
	bool rightClick = false;
	bool draw = false;
	bool secondPointSet = false;
	bool start = true;
	bool canStartANewLine = true;*/


	if (!draw && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//start = false;
		draw = true;

		newLineSetStart = i;
		finishing = false;

		MapLines.append(sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
		MapLines[i].color = sf::Color::Red;
		MapLines.append(sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
		MapLines[i + 1].color = sf::Color::Red;
	}



	if (!canStartANewLine && !sf::Mouse::isButtonPressed(sf::Mouse::Left) && draw)
		canStartANewLine = true;


	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && draw)
		MapLines[i + 1].position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (canStartANewLine && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		canStartANewLine = false;
		i += 2;
		MapLines.append(MapLines[i - 1]);
		MapLines[i].color = sf::Color::Red;
		MapLines.append(sf::Vertex(window.mapPixelToCoords(sf::Mouse::getPosition(window))));
		MapLines[i + 1].color = sf::Color::Red;
	}


	if (draw && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		draw = false;
			//i = i - 2;
		//	MapLines.c
		MapLines.resize(MapLines.getVertexCount() - 2);
		
	}

	if (!draw && sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !finishing) { //complete the line set by connecting end to start
		MapLines.append(MapLines[i - 1]);
		MapLines[i].color = sf::Color::Red;
		MapLines.append(MapLines[newLineSetStart]);
		MapLines[i + 1].color = sf::Color::Red;

		finishing = true;

		i += 2;
	}



}

Point MapGenerator::intersection(const Point& point1, const Point& point2, const Point& mousepoint)
{

	float m1 = point2.x > point1.x ? (point2.y - point1.y) / (point2.x - point1.x) : (point1.y - point2.y) / (point1.x - point2.x);

	float m2 = -1.f / m1;

	//point1 on line
	// y = mx + c
	// intercept c = y - mx
	float intersection_X;
	float intersection_Y;
	float c1;
	float c2;

	if (isinf(m2)) {
		c1 = point1.y - m1 * point1.x;
		intersection_X = mousepoint.x;
		intersection_Y = m1 * intersection_X + c1;
	}
	else if (isinf(m1)) {
		c2 = mousepoint.y - m2 * mousepoint.x;
		intersection_X = point1.x;
		intersection_Y = m2 * intersection_X + c2;
	}
	else {
		c1 = point1.y - m1 * point1.x;

		c2 = mousepoint.y - m2 * mousepoint.x;

		assert((m1 - m2) != 0.0f);
		intersection_X = (c2 - c1) / (m1 - m2);
		intersection_Y = m1 * intersection_X + c1;
	}

	return Point{ intersection_X,intersection_Y };
	
}

int MapGenerator::attach(Point& mousepoint)
{
	size_t size = MapLines.getVertexCount();
	bool found = false;
	int attachPosition;
	for (int count=0; count!=size; count+=2)
		if (isClose(MapLines[count].position, MapLines[count + 1].position, mousepoint)) {
			found = true;
			attachPosition = count;
			break;
		}

	if (found)
		return attachPosition;
	else 
		return -1;

	//  while(true){
	//	//i += 2;
	//	attachPoint[0].position = findAttachPoint(;
	//	MapLines.append(attachPoint[0].position);
	//	MapLines[i].color = sf::Color::Red;
	//	MapLines.append(mousepoint);
	//	MapLines[i + 1].color = sf::Color::Red;
	//	draw = true;
	//}

}

bool MapGenerator::isClose(const Point& point1, const Point& point2, const Point& mousepoint)
{
	float slope = point2.x > point1.x ? (point2.y - point1.y) / (point2.x - point1.x) : (point1.y - point2.y) / (point1.x - point2.x);

	if (isinf(slope))
		return (mousepoint.x - point1.x)*(mousepoint.x - point1.x) < attachDistanceSquared;
	else
		return pow((slope*mousepoint.x - mousepoint.y + (point1.y - slope*point1.x)), 2) / (slope*slope + 1) < attachDistanceSquared; // (mx-y-(y1-mx1)|/(m*m+1)
}

Point MapGenerator::findAttachPoint(Point& mousepoint, int& attachPosition)
{
	Vector ab = MapLines[attachPosition + 1].position - MapLines[attachPosition].position;
	Vector ap = mousepoint - MapLines[attachPosition].position;
	
	float fractionalProjection = (ap.x*ab.x + ap.y*ab.y) / (ab.x*ab.x + ab.y*ab.y);

	if (fractionalProjection > 0.999f)
		return MapLines[attachPosition + 1].position;
	if(fractionalProjection<0.001f)
		return MapLines[attachPosition].position;


	float x0 = fractionalProjection*ab.x + MapLines[attachPosition].position.x;
	float y0 = fractionalProjection*ab.y + MapLines[attachPosition].position.y;

	

	return Point(x0, y0);

}

void MapGenerator::writeToFile()
{
	std::ofstream mapFile("mapfile");


	if (mapFile.is_open())
		mapFile.clear();

	size_t size = MapLines.getVertexCount();
	size_t j = 0;

	while (mapFile && j!=size) {
		mapFile << MapLines[j].position.x << "," << MapLines[j].position.y << ";"<<std::endl;
		j += 1;
	}

	mapFile.close();
		
	
}


void MapGenerator::readTileMap()
{
	// create the window
	//sf::RenderWindow window(sf::VideoMode(640, 480), "Tilemap");


	// define the level with an array of tile indices
	const int level[] =
	{
		1,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2,2,2,2,15,2,2,2,2,2,2,2,2,2,2,2,3,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,12,2,2,2,2,2,10,16,16,6,2,2,2,2,2,8,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,9,10,16,16,6,2,2,2,2,2,2,2,8,
		5,16,16,16,16,16,16,16,16,16,16,16,11,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,
		12,2,2,2,2,2,2,2,2,2,2,2,3,16,16,16,16,16,16,16,16,16,16,16,16,16,16,1,2,2,2,2,2,2,10,16,16,6,2,8,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		12,2,2,2,2,2,2,2,2,2,2,2,7,16,16,16,16,16,16,16,16,16,16,16,16,16,16,12,10,16,16,6,2,2,2,2,2,2,2,8,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		5,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,16,5,16,16,16,16,16,16,16,16,16,16,16,5,
		9,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,14,2,2,2,2,2,2,2,2,2,2,2,7
	};

	// create the tilemap from the level definition

	if (!background.load("tileset.png", sf::Vector2u(32, 32), level, 40, 30))
		throw std::runtime_error("couldn't load tileset.png");

	//background.scale(sf::Vector2f(.5f, .5f));


}