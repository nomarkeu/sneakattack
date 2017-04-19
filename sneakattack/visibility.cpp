#include "stdafx.h"
#include <vector>
#include <iostream>
#include <array>
#include <vector>
#include <limits>
#include <set>
#include "Character.h"
#include "visibility.h"

int Round(float x) {
	assert(x >= LONG_MIN - 0.5);
	assert(x <= LONG_MAX + 0.5);
	if (x >= 0)
		return (int)(x + 0.5);
	return (int)(x - 0.5);
}

void visibility(const vector<Segment>& linesegments, vector<Pointmap>& allpoints, const Point& location, Triangles& visibilityPolygon)
{
	const Point& observer = location;
	AngleComparator compare(observer);
	
	sort(allpoints.begin(), allpoints.end(), compare);

	sf::VertexArray visibleTriangle(sf::Triangles, 3);
	sf::Vertex* triangle = &visibleTriangle[0];
	triangle[0].position = observer;
	lineSegmentCompare segCompare(observer);
	vector<Segment> intersectingSegments;
	Segment insight;
	bool first = true;
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
}




