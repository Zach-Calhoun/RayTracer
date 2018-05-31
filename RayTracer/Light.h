#pragma once
#include "Vector.h"
class PointLight
{
public:
	Vector pos;
	Vector color;
	double energy;
	PointLight();
	PointLight(const PointLight& p);
	PointLight(Vector p, Vector c, double e);
};