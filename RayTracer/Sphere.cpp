#include "Sphere.h"

Sphere::Sphere()
{
	origin = Vector();
	radius = 10;
	//color = Vector(1, 0, 0);
}

Sphere::Sphere(Vector o, double r, Material m)
{
	origin = o;
	radius = r;
	mat = m;
}

Intersection Sphere::Trace(Ray& r)
{
	Vector rayToSphere = origin - r.origin;

	//ray starts inside of sphere
	//discard because by convention
	//we discard backfaces
	if (rayToSphere * r.direction < 0)
	{
		return Intersection();
	}
	else
	{
		//project cententer of sphere on direction
		//correct only if camera is always in origin!!!
		//Vector scp = r.direction * (origin * r.direction);
		Vector scp = r.direction * (rayToSphere * r.direction);
		double distFromCenterToRay = (rayToSphere - scp).length();
		//ray misses the sphere
		if (distFromCenterToRay > radius)
		{
			return Intersection();
		}
		else
		{
			double dist = sqrt(radius*radius - distFromCenterToRay * distFromCenterToRay);
			double distToHit = 0;
			if (rayToSphere.length() > radius)
			{
				//distToHit = (scp - r.origin).length() - dist;
				distToHit = (scp).length() - dist;
			}
			else
			{
				distToHit = (scp).length() + dist;
				//distToHit = (scp - r.origin).length() + dist;
			}

			Vector hit = r.origin + (r.direction * distToHit);
			Vector norm = hit - origin;
			norm.normalize();
			Intersection result = Intersection();
			result.matInfo = mat.GetMatInfo();
			result.hit = hit;
			result.success = true;
			result.normal = norm;
			return result;
		}
	}

}