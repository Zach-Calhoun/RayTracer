#include "Primitives.h"

Ray::Ray()
{
	origin = Vector();
	direction = Vector(0, 0, 1);
}

Ray::Ray(Vector o, Vector d)
{
	origin = o;
	direction = d;
}

Intersection Ray::Trace(RayTraceable& o)
{
	return o.Trace(*this);
}