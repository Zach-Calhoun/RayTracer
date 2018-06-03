#pragma once
#include "RayTraceable.h"

class Sphere : public RayTraceable
{
public:
	Vector origin;
	double radius;
	//Vector color;


	Sphere();
	Sphere(Vector o, double r, Material mat = Material(Vector(0.5,0.5,0.5)));
	Intersection Trace(Ray& r);

};
