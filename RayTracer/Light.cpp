#include "Light.h"

PointLight::PointLight()
{
	pos = Vector();
	color = Vector(1, 1, 1);
	energy = 1000;
}

PointLight::PointLight(Vector p, Vector c, double e)
{
	pos = p;
	color = c;
	energy = e;
}

PointLight::PointLight(const PointLight& p)
{
	pos = Vector(p.pos);
	color = Vector(p.color);
	energy = p.energy;
}