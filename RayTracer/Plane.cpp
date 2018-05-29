#include "Primitives.h"
Plane::Plane()
{
	normal = Vector(0, 1, 0);
	distance = 500;
	//Plane
}

Plane::Plane(Vector n, double d, Vector c)
{
	normal = n.normalize();
	distance = d;
	color = c;
}
Intersection Plane::Trace(Ray& r)
{
	double dot = r.direction * normal;
	if (dot > -FLT_EPSILON)
	{
		//plane is paralel or backwards facing
		return Intersection();
	}
	else
	{
		//intersection exists
		Vector planePoint = -normal * distance;
		double dist = (planePoint - r.origin) * normal / dot;	
		if (dist < 0) {
			return Intersection();
		}
		//dist = abs(dist);
		Vector hit = r.origin + (r.direction * dist);
		Intersection result = Intersection();
		result.success = true;
		result.hit = hit;
		result.color = color;
		result.normal = normal;
		return result;
	}
}
