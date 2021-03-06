#pragma once
#include "RayTraceable.h"

class Plane : public RayTraceable
{
public:
	Vector normal;
	double distance;
	//Vector color;

	Plane();
	Plane(Vector n, double d, Material* m = new Material(Vector(0.5,0.5,0.5)));
	Intersection Trace(Ray& r);
	Vector GetPos();
	void SetPos(Vector p);
};
