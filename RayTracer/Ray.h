#pragma once
#include "Vector.h"
#include "Intersection.h"
#include "Light.h"
#include <vector>
//#include "RayTraceable.h"
using namespace std;
class RayTraceable;

class Ray
{
private:
	Intersection Trace(RayTraceable& o);
public:
	Vector origin;
	Vector direction;

	Ray();
	Ray(Vector o, Vector d);
	Intersection TraceObjects(vector<RayTraceable*>& objects);
	Intersection TraceLight(vector<RayTraceable*>& objects, PointLight& light);
	Intersection TraceReflection(vector<RayTraceable*>& objects, int maxDepth);

};