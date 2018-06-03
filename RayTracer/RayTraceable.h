#pragma once
//#include "Material.h"
#include "Ray.h"

//class Ray;

class RayTraceable
{
protected:
	RayTraceable();
public:
	Material mat;
	virtual Intersection Trace(Ray& r) = 0;
};