#pragma once
//#include "Vector.h"
#include "Material.h"

class Intersection
{
public:
	Vector hit;
	MaterialInfo matInfo;
	Vector normal;
	bool success;


	Intersection();
};
