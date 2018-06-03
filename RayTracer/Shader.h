#pragma once
#include "Vector.h"
#include "Intersection.h"
#include "Ray.h"
#include "Scene.h"

class Shader
{
public:
	static Vector CalculateShading(Intersection& hit, Ray& view, Scene* scene, int renderMode, int& depth);

};