#include "stdafx.h"
#include <vector>
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <set>
#include "Character.h"

int Round(float x) {
	assert(x >= LONG_MIN - 0.5);
	assert(x <= LONG_MAX + 0.5);
	if (x >= 0)
		return (int)(x + 0.5);
	return (int)(x - 0.5);
}

// implement collinear check

//void visibility(Triangles& visibilityPolygon,const Point& observer, const vector<Segment>& linesegments, const vector<Pointmap>& allpoints)
void Player::visibility(const vector<Segment>& linesegments, vector<Pointmap>& allpoints)
{
	//sort(linesegments.begin(), linesegments.end());
	
	const Point& observer = location;
	//observer.x = Round(location.x);
	//observer.y=Round(location.y);

	AngleComparator compare(observer);

	//vector<Segment> linesegments;
	//vector<Pointmap> allpoints;
	//mapreader(linesegments, allpoints);

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
	triangle[0].color = triangle[1].color = triangle[2].color = sf::Color(151,204,239,100);

	lineSegmentCompare segCompare(observer);

	//std::set<Segment, lineSegmentCompare> intersectingSegments{segCompare};
	vector<Segment> intersectingSegments;

	Segment insight;

	bool first = true;

	//bool fixtriangle = false;

	for (const auto& point : allpoints) {
		
		if (first) {
			for (const auto& segment : linesegments)
				if (intersecting(segment, point.second, observer) && !(coincidentLeftTurn(segment, point.second, observer)))
					intersectingSegments.push_back(segment);
			std::sort(intersectingSegments.begin(), intersectingSegments.end(), segCompare);
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
			
			for (const auto& segment : linesegments)
				if (intersecting(segment, point.second, observer) && !approx_equal(segment,insight) && !coincidentLeftTurn(segment,point.second,observer))
					intersectingSegments.push_back(segment);
		//	intersectingSegments;
			//intersectingSegments.erase(insight);
			std::sort(intersectingSegments.begin(), intersectingSegments.end(), segCompare);
			insight = *intersectingSegments.begin();
			intersectingSegments.clear();
			triangle[1].position = intersection(insight, point.second, observer);
			continue;
		}
		else {
			for (const auto& segment : linesegments)
				if (intersecting(segment, point.second, observer))
					intersectingSegments.push_back(segment);
			//intersectingSegments.push_back(insight);
			std::sort(intersectingSegments.begin(), intersectingSegments.end(), segCompare);
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

	for (auto& point : allpoints) {
			if (approx_equal(point.second, insight[0]) || approx_equal(point.second, insight[1])) {
			triangle[2].position = point.second;
			visibilityPolygon.append(triangle);
			if (whichside(visibilityPolygon.begin(), insight)==0)
				visibilityPolygon.tieUpTheEnds(observer);
			break;

			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer) && !approx_equal(segment, insight))
					intersectingSegments.push_back(segment);
			//	intersectingSegments;
			//intersectingSegments.erase(insight);
			std::sort(intersectingSegments.begin(), intersectingSegments.end(), segCompare);
			insight = *intersectingSegments.begin();
			intersectingSegments.clear();
			triangle[1].position = intersection(insight, point.second, observer);
			continue;
		}
		else {
			for (auto& segment : linesegments)
				if (intersecting(segment, point.second, observer))
					intersectingSegments.push_back(segment);
			//intersectingSegments.push_back(insight);
			std::sort(intersectingSegments.begin(), intersectingSegments.end(), segCompare);
			if (approx_equal(insight, *intersectingSegments.begin())) {
				intersectingSegments.clear();
				continue;
			}
			else {
				triangle[2].position = intersection(insight, point.second, observer);
				visibilityPolygon.append(triangle);
				if (whichside(visibilityPolygon.begin(), insight) == 0)
					visibilityPolygon.tieUpTheEnds(observer);
				break;
				insight = *intersectingSegments.begin();
				intersectingSegments.clear();
				triangle[1].position = intersection(insight, point.second, observer);
				;
			}
		}


	}


	//

}




