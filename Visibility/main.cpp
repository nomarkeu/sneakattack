#include "stdafx.h"
#include <array>
#include <vector>
#include <iostream>
#include "visibility.h"
#include "map.h"


int main()
{
	//Triangles visibilityPolygon;
	//vector<Segment> linesegments; //map
	Point observer;
	observer.x = 552.124695f;
	observer.y = 554.683105f;
	//visibility(visibilityPolygon, observer, linesegments);
	//sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Visibility");
	//

	//RectangleMap map(linesegments);

	//		
	//while (window.isOpen()) {
	//	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	//		window.close();

	//	window.clear(sf::Color::White);
	//	window.draw(visibilityPolygon);
	//	window.draw(map);
	//	window.display();
	//}

	/*lineSegmentCompare compare(observer);

	Point s1a({846.000000,221.000000 });
	Point s1b({ 846.000000,330.000000 });
	Point s2a({ 595.000000, 251.000000 });
	Point s2b({ 606.000000, 251.000000 });


	Segment s1({ s1a,s1b });
	Segment s2({ s2a,s2b });

	bool s = compare(s2, s1);*/

	Point a1({ 595.000000f,506.000000f});
	Point a2({ 846.000000f,221.000000f });

	Pointmap p1(15,a1);
	Pointmap p2(17,a2);

	AngleComparator compare(observer);

	bool angle = compare(p1, p2);

	return 0;
}