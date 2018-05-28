#pragma once
#include "Vector.h"
class PointLight
{
public:
	Vector pos;
	Vector color;
	double energy;
	PointLight();
	PointLight(Vector p, Vector c, double e);
};