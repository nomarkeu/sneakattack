#pragma once
#include "sfml/Graphics.hpp"

typedef sf::Vector2f Vector;
typedef sf::Vector2f Point;

bool SATCollision(std::array<Point, 4> R1a, std::array<Point, 4> R2a, Vector& projectionVector);