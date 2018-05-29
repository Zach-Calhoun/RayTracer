// RayCaster.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "config.h"
#include "Primitives.h"
#include "Light.h"
#include <fstream>
#include <vector>

int main()
{
	Camera cam = Camera();
	cam.pos = Vector(0, 0, 0);
	
	//Sphere sp = Sphere(Vector(0, 0, 1000), 100, Vector(1,0,0));
	std::ofstream output = std::ofstream("result.ppm");
	output << "P3" << std::endl;
	output << SCREEN_WIDTH << " " << SCREEN_HEIGHT << std::endl;
	output << 255 << std::endl;
	std::vector<RayTraceable*> objects = std::vector<RayTraceable*>();
	objects.push_back(new Plane(Vector(0, 1, 0), 1, Vector(1, 1, 0)));
	objects.push_back(new Plane(Vector(1, 0, 0), 7, Vector(1, 0, 0)));
	//objects.push_back(new Sphere(Vector(-200, 0, 200), 50, Vector(1, 0, 0)));
	objects.push_back(new Sphere(Vector(0, 1, 3), 1, Vector(0, 0, 1)));
	//objects.push_back(new Sphere(Vector(200, 150, 300), 10, Vector(0, 1, 1)));
	//objects.push_back(new Sphere(Vector(-100, -70, 180), 10, Vector(0, 1,0)));
	//objects.push_back(new Plane(Vector(1, 1, 0), 900, Vector(1, 0, 0)));

	PointLight light = PointLight(Vector(-1, 4, 1), Vector(1, 1, 1), 50);

	for (int i = 0; i < SCREEN_HEIGHT;i++)
	{
		for (int j = 0; j < SCREEN_WIDTH; j++)
		{
			Ray r = cam.GenerateRay(i, j);
			Intersection hit = Intersection();
			double min_dist = INFINITY;
			for (int k = 0; k < objects.size(); k++)
			{
				RayTraceable* object = objects[k];
				Intersection tmpHit = r.Trace(*object);
				if (tmpHit.success) {
					if (tmpHit.hit.length() < min_dist)
					{
						min_dist = tmpHit.hit.length();
						hit = tmpHit;
					}
				}
			}
			if (hit.success)
			{
				//calc basic light
				Vector lightDir = (light.pos - hit.hit);
				double lightDistance = lightDir.length();

				Ray shadowRay = Ray(hit.hit, lightDir.normalized());
				//add small forward to prevent self collison
				shadowRay.origin = shadowRay.origin + (lightDir.normalized() * 0.0001);
				Intersection shadowHit = Intersection();
				for (int l = 0; l < objects.size(); l++)
				{
					shadowHit = shadowRay.Trace(*objects[l]);
					if (shadowHit.success && shadowHit.hit.length() < lightDistance)
					{
						break;
					}
				}
				double intensity = 0;
				if (shadowHit.success && shadowHit.hit.length() < lightDistance)
				{
					intensity = AMBIENT_LEVEL;
				}
				else
				{
					intensity = lightDir.normalized() * hit.normal;
				}

				
				if (intensity < AMBIENT_LEVEL)
				{
					intensity = AMBIENT_LEVEL;
				}
				Vector finalColor = hit.color.blend(light.color) * intensity * (light.energy / (lightDistance * lightDistance));
				output << finalColor;
			}
			else
			{
				output << 255 << " " << 255 << " " << 255 << " ";
			}
			 //= r.Trace(sp);
			
			//Ray r = Ray(); //defaults to world origin and forward direction ( +z )
			//std::cout << "Y: " << i << " X: " << j << " " << hit.color.r() << " " << hit.color.g() << " " << hit.color.b() << " " << std::endl;
		}
		output << std::endl;
	}

	output.close();

    return 0;
}

