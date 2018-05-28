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
	
	//Sphere sp = Sphere(Vector(0, 0, 1000), 100, Vector(1,0,0));
	std::ofstream output = std::ofstream("result.ppm");
	output << "P3" << std::endl;
	output << SCREEN_WIDTH << " " << SCREEN_HEIGHT << std::endl;
	output << 255 << std::endl;
	std::vector<RayTraceable*> objects = std::vector<RayTraceable*>();
	objects.push_back(new Sphere(Vector(-200, 0, 500), 100, Vector(1, 0, 0)));
	objects.push_back(new Sphere(Vector(0, 0, 400), 50, Vector(0, 0, 1)));
	objects.push_back(new Sphere(Vector(200, 150, 400), 50, Vector(0, 1, 1)));
	objects.push_back(new Sphere(Vector(-100, -70, 300), 50, Vector(0, 1,0)));

	PointLight light = PointLight(Vector(0, 500, 0), Vector(1, 1, 1), 100000);

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
				double intensity = lightDir.normalized() * hit.normal;
				if (intensity < 0)
				{
					intensity = AMBIENT_LEVEL;
				}
				Vector finalColor = hit.color * intensity * (light.energy / (lightDistance * lightDistance));
				output << finalColor;
			}
			else
			{
				output << 0 << " " << 0 << " " << 0 << " ";
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

