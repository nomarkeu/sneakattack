#include "stdafx.h"
#include "SATCollision.h"
#include <array>
#include <assert.h>

bool SATCollision(std::array<Point,4> R1, std::array<Point,4> R2, Vector& projectionVector) {

	std::array<Vector,4> axes;

	axes[0] = R1[1] - R1[0];
	axes[1] = R1[2] - R1[1];
	axes[2] = R2[1] - R2[0];
	axes[3] = R2[2] - R2[1];

	float R1min=100000.f, R1max=0.f, R2min=100000.f, R2max=0.f, projection = 0,overlap=0, minOverlap = 100000.f;
	float axismagnitude = 0;



	Vector minaxis;

	for (auto& axis : axes) {
		for (auto& point : R1) {
			projection = axis.x*point.x + axis.y*point.y;
			R1min = std::min(projection, R1min);
			R1max = std::max(projection, R1max);
		}
		for (auto& point : R2) {
			projection = axis.x*point.x + axis.y*point.y;
			R2min = std::min(projection, R2min);
			R2max = std::max(projection, R2max);
		}

		if (R1max<R2min || R1min>R2max)
			return false;
		
		axismagnitude = sqrt(axis.x*axis.x + axis.y*axis.y);
		overlap = (R2max - R2min + R1max - R1min - ( std::max(R1max, R2max) - std::min(R1min, R2min) ))/axismagnitude;
		minOverlap= std::min(minOverlap, overlap);
		if (!(minOverlap < overlap))
			minaxis = axis;
		R1min = 100000.f; R1max = 0.f; R2min = 100000.f; R2max = 0.f; 
	}
		
	float magnitude = sqrt(minaxis.x*minaxis.x + minaxis.y*minaxis.y);
	projectionVector = minaxis*(minOverlap)/ magnitude;

	Point R1centre, R2centre;
	float xmax = 0.f, xmin = 10000.f , ymax = 0.f, ymin = 10000.f;

	for (auto& point : R1) {
		xmax = std::max(xmax, point.x);
		xmin = std::min(xmin, point.x);
		ymax = std::max(ymax, point.y);
		ymin = std::min(ymin, point.y);
	}

	R1centre = Point((xmax + xmin)/2.0f, (ymax + ymin)/2.0f);

	xmax = 0.f; xmin = 10000.f; ymax = 0.f; ymin = 10000.f;

	for (auto& point : R2) {
		xmax = std::max(xmax, point.x);
		xmin = std::min(xmin, point.x);
		ymax = std::max(ymax, point.y);
		ymin = std::min(ymin, point.y);
	}

	R2centre = Point((xmax + xmin) / 2.0f, (ymax + ymin) / 2.0f);

	Vector towardsR2 = R2centre - R1centre;

	if ((towardsR2.x*projectionVector.x + towardsR2.y*projectionVector.y) < 0)
		projectionVector = projectionVector*-1.0f;
//	assert(projectionVector.y < 0.00000001f);

	return true;
}