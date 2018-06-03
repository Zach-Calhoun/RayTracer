#include "Ray.h"
#include "RayTraceable.h"
#include "Light.h"

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

Intersection Ray::TraceObjects(vector<RayTraceable*>& objects)
{
	Intersection hit;
	double min_dist = INFINITY;
	for (int k = 0; k < objects.size(); k++)
	{
		RayTraceable* object = objects[k];
		Intersection tmpHit = Trace(*object);
		if (tmpHit.success) {
			double distToHit = origin.dist(tmpHit.hit);
			if (distToHit < min_dist)
			{
				min_dist = distToHit;
				hit = tmpHit;
			}
		}
	}
	return hit;
}

Intersection Ray::TraceLight(vector<RayTraceable*>& objects, PointLight& light)
{
	Vector rayToLight = light.pos - origin;
	Vector lightDir = rayToLight.normalized();
	origin = origin + (lightDir * 0.001);
	double lightDistance = rayToLight.length();
	Intersection shadowHit;
	for (int i = 0; i < objects.size(); i++)
	{
		shadowHit = Trace(*objects[i]);
		if (shadowHit.success && origin.dist(shadowHit.hit) < lightDistance)
		{
			break;
		}
		else
		{
			shadowHit.success = false;
		}
	}
	return shadowHit;
}

Intersection Ray::TraceReflection(vector<RayTraceable*>& objects, int maxDepth) 
{
	return Intersection();
}