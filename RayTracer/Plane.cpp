#include "Plane.h"

Plane::Plane()
{
	normal = Vector(0, 1, 0);
	distance = 500;
	//Plane
}

Plane::Plane(Vector n, double d, Material m)
{
	normal = n.normalize();
	distance = d;
	mat = m;
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
		Vector rayToPlane = planePoint - r.origin;
		double dist = rayToPlane * -normal;
		//Vector nearestPointToRayOrigin = -normal * dist;
		Vector hit = r.origin +( r.direction * dist * (-1.0 / dot));
		Intersection result = Intersection();
		result.success = true;
		result.hit = hit;
		result.matInfo = mat.GetMatInfo();
		result.normal = normal;
		return result;
		//double dist = rayToPlane * normal / dot;
		////double dist = rayToPlane * normal / (rayToPlane.normalized() * normal);
		//if (dist < 0) {
		//	return Intersection();
		//}
		////dist = abs(dist);
		//Vector hit = r.origin + (r.direction * dist);
		//Intersection result = Intersection();
		//result.success = true;
		//result.hit = hit;
		//result.color = color;
		//result.normal = normal;
		//return result;
	}
}
