#include "Primitives.h"

Sphere::Sphere()
{
	origin = Vector();
	radius = 10;
	color = Vector(1, 0, 0);
}

Sphere::Sphere(Vector o, double r, Vector c)
{
	origin = o;
	radius = r;
	color = c;
}

Intersection Sphere::Trace(Ray& r)
{

}