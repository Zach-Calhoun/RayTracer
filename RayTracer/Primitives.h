#pragma once
#include "Vector.h"
#include "Matrix.h"
//#include <stdlib.h>
//#include 
class Ray;
class Scene;

class Intersection
{
public:
	Vector hit;
	Vector color;
	Vector normal;
	bool success;


	Intersection();
};

class RayTraceable
{
public:
	virtual Intersection Trace(Ray& r) = 0;
};

class Ray
{
public:
	Vector origin;
	Vector direction;

	Ray();
	Ray(Vector o, Vector d);
	Intersection Trace(RayTraceable& o);
};




//eventualy theese will contain a material type object
class Sphere : public RayTraceable
{
public:
	Vector origin;
	double radius;
	Vector color;
	

	Sphere();
	Sphere(Vector o, double r, Vector c);
	Intersection Trace(Ray& r);

};

class Plane : public RayTraceable
{
public:
	Vector normal;
	double distance;
	Vector color;

	Plane();
	Plane(Vector n, double d, Vector c);
	Intersection Trace(Ray& r);
};
