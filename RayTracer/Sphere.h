#pragma once
#include "RayTraceable.h"

class Sphere : public RayTraceable
{
public:
	Vector origin;
	double radius;
	//Vector color;


	Sphere();
	Sphere(Vector o, double r, Material* mat = new Material(Vector(0.5,0.5,0.5)));
	Sphere(Vector o, double r, Vector mat);
	Intersection Trace(Ray& r);
	Vector GetPos();
	void SetPos(Vector p);
};
