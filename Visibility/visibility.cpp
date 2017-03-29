#include "stdafx.h"
#include <vector>
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <set>
#include "visibility.h"
// implement collinear check

void visibility(Triangles& visibilityPolygon,const Point& observer)
{
	
	

	//sort(linesegments.begin(), linesegments.end());
		
	AngleComparator compare(observer);

	vector<Segment> linesegments;
	vector<Pointmap> allpoints;
	mapreader(linesegments, allpoints);

	/*for (auto point : allpoints) {
		std::cout << point.first<<": "<<point.second.x << ", " << point.second.y << std::endl;
	}
	std::cout << "-----------" << std::endl;
	getchar();

	for (auto a : allpoints)
		for (auto b : allpoints)
			std::cout << compare(a, b)<<std::endl;
	getchar();*/


	sort(allpoints.begin(), allpoints.end(), compare);
	
	

	//vector<Pointmap>::iterator one = allpoints.begin() + 4;
	//vector<Pointmap>::iterator  two = allpoints.begin() + 8;
	
	//vector<Pointmap> temp(one,two);

	//allpoints[4] = std::pair<int,Point>(12, {1209.00000 ,105.000000 });
	//allpoints[5] = std::pair<int, Point>(10, {696.000000 ,392.000000 });
	//allpoints[6] = std::pair<int, Point>(11, {336.000000 ,392.000000 });
	//allpoints[7] = std::pair<int, Point>(3, {11.0000000 ,676.000000 });
	//allpoints;
	//
	
	/*for (auto point : allpoints) {
		std::cout << point.first << ": "<<point.second.x << ", " << point.second.y << std::endl;
	}
	
	getchar();*/

	sf::VertexArray visibleTriangle(sf::Triangles, 3);
	sf::Vertex* triangle = &visibleTriangle[0];

	
		
	triangle[0].position = observer;
	triangle[0].color = triangle[1].color = triangle[3].color= sf::Color::Blue;

	lineSegmentCompare segCompare(observer);

	std::set<Segment, lineSegmentCompare> intersectingSegments{segCompare};

	Segment insight;

	bool first = true;

	for (auto& point : allpoints) {
		
		if (first) {
			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer))
					intersectingSegments.insert(segment);
		
			insight = *intersectingSegments.begin();
			intersectingSegments.clear();
			triangle[1].position = intersection(insight, point.second, observer);
			first = false;
			continue;
		}
/*--------------------------------------------------------------------------*/
		if (approx_equal(point.second, insight[0]) || approx_equal(point.second, insight[1])) {
			triangle[2].position = point.second;
			visibilityPolygon.append(triangle);
			
			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer) && !approx_equal(segment,insight) && !coincidentLeftTurn(segment,point.second,observer))
					intersectingSegments.insert(segment);
		//	intersectingSegments;
			//intersectingSegments.erase(insight);
			insight = *intersectingSegments.begin();
			intersectingSegments.clear();
			triangle[1].position = intersection(insight, point.second, observer);
			continue;
		}
		else {
			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer))
					intersectingSegments.insert(segment);
			intersectingSegments.insert(insight);
			if (approx_equal(insight, *intersectingSegments.begin())) {
				intersectingSegments.clear();
				continue;
			}
			else {
				triangle[2].position = intersection(insight, point.second, observer);
				visibilityPolygon.append(triangle);
				insight = *intersectingSegments.begin();
				intersectingSegments.clear();
				triangle[1].position = intersection(insight, point.second, observer);
				;
			}
		}
	}

	//after last point

	/*auto& point = allpoints[0];
	if (approx_equal(point.second, insight[0]) || approx_equal(point.second, insight[1])) {
		triangle[2].position = point.second;
		;
	}
	else {
		for (auto& segment : linesegments)
			if (intersecting(segment, point.second, observer))
				intersectingSegments.insert(segment);
			triangle[2].position = intersection(insight, point.second, observer);
			visibilityPolygon.append(triangle);
		}
	*/

	for (int i = 0; i != 2; i++) {
		Pointmap& point = allpoints[i];
		if (approx_equal(point.second, insight[0]) || approx_equal(point.second, insight[1])) {
			triangle[2].position = point.second;
			visibilityPolygon.append(triangle);

			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer) && !approx_equal(segment, insight))
					intersectingSegments.insert(segment);
			//	intersectingSegments;
			//intersectingSegments.erase(insight);
			insight = *intersectingSegments.begin();
			intersectingSegments.clear();
			triangle[1].position = intersection(insight, point.second, observer);
			continue;
		}
		else {
			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer))
					intersectingSegments.insert(segment);
			intersectingSegments.insert(insight);
			if (approx_equal(insight, *intersectingSegments.begin())) {
				intersectingSegments.clear();
				continue;
			}
			else {
				triangle[2].position = intersection(insight, point.second, observer);
				visibilityPolygon.append(triangle);
				insight = *intersectingSegments.begin();
				intersectingSegments.clear();
				triangle[1].position = intersection(insight, point.second, observer);
				;
			}
		}


	}


}




