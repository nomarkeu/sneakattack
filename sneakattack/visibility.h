#pragma once
#include "utilities.h"
#include "visibilitypolygon.h"
//#include "Character.h"

void visibility(const vector<Segment>& linesegments, vector<Pointmap>& allpoints, const Point& location, Triangles& visibilityPolygon);