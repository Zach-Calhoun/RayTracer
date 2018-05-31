#include "Primitives.h"
#include "Scene.h"
#include "config.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>

Camera::Camera()
{
	pos = Vector();
	rot = Vector();
	

	screenHeight = SCREEN_HEIGHT;
	screenWidth = SCREEN_WIDTH;
	verticalFov = ((double)V_FOV / 180) * M_PI;
	horizontalFov = ((double)H_FOV / 180) * M_PI;

	buffer = new Vector*[screenHeight];
	for (int i = 0; i < screenHeight; i++)
	{
		buffer[i] = new Vector[screenWidth];
	}

	CalculateRayConstants();
}

Camera::Camera(int h, int w, double v_fov, double h_fov)
{
	screenHeight = h;
	screenWidth = w;
	verticalFov = (v_fov / 180) * M_PI;
	horizontalFov = (h_fov / 180) * M_PI;

	buffer = new Vector*[screenHeight];
	for (int i = 0; i < screenHeight; i++)
	{
		buffer[i] = new Vector[screenWidth];
	}

	CalculateRayConstants();
}

void Camera::Setup(int h, int w, double v_fov, double h_fov)
{
	screenHeight = h;
	screenWidth = w;
	verticalFov = (v_fov / 180) * M_PI;
	horizontalFov = (h_fov / 180) * M_PI;
	CalculateRayConstants();

	for (int i = 0; i < screenHeight; i++)
	{
		delete[] buffer[i];
	}
	delete[] buffer;

	buffer = new Vector*[screenHeight];
	for (int i = 0; i < screenHeight; i++)
	{
		buffer[i] = new Vector[screenWidth];
	}
}

void Camera::CalculateRayConstants()
{
	//after some drawings on a piece of paper
	int halfWidth = screenWidth / 2;
	double beta = (M_PI - horizontalFov) / 2;
	double cosBeta = cos(beta);
	focalLength = sqrt(halfWidth * halfWidth * (1 / (cosBeta * cosBeta) - 1)) / 250; //divide so camera fustrum size is more managable
	double halfVFovCos = cos(verticalFov / 2);
	double vFovFactor = 1 / (halfVFovCos * halfVFovCos);
	double allowedHeight = 2 * sqrt((focalLength * focalLength) * (vFovFactor - 1));
	heightFactor =  allowedHeight / screenHeight;
}

Ray Camera::GenerateRay(int y, int x)
{
	//get relative pos in camera space
	//after some drawings on a piece of paper
	double cam_x = ((double)x - (screenWidth / 2)) / 250;
	//double ray_y = ((double)y / screenHeight) * heightFactor;
	double cam_y = ((screenHeight / 2) - y) * heightFactor;

	Vector dir = Vector(cam_x, cam_y, focalLength);
	Ray ray = Ray(pos, dir.normalized());
	
	return ray;
	//TODO: Apply camera rotation to generated vector

}

void Camera::LookAt(Vector v)
{

}

void Camera::Render(Scene& scene)
{
	#define objects scene.objects

	for (int i = 0; i < screenHeight; i++)
	{
		for (int j = 0; j < screenWidth; j++)
		{
			Ray r = GenerateRay(i, j);
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
				#define light scene.lights[0]
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
					if (shadowHit.success && (shadowRay.origin.dist(shadowHit.hit)) < lightDistance)
					{
						break;
					}
				}
				double intensity = 0;
				if (shadowHit.success && (shadowRay.origin.dist(shadowHit.hit)) < lightDistance)
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
				buffer[i][j] = finalColor;
			}
			else
			{
				buffer[i][j] = Vector(1, 1, 1);
			}
			//= r.Trace(sp);

			//Ray r = Ray(); //defaults to world origin and forward direction ( +z )
			//std::cout << "Y: " << i << " X: " << j << " " << hit.color.r() << " " << hit.color.g() << " " << hit.color.b() << " " << std::endl;
		}	
	}

}

bool Camera::SavePpm(char * path)
{
	try
	{
		std::ofstream output = std::ofstream(path);
		output << "P3" << std::endl;
		output << screenWidth << " " << screenHeight << std::endl;
		output << 255 << std::endl;
		for (int i = 0; i < screenHeight; i++)
		{
			for (int j = 0; j < screenWidth; j++)
			{
				output << buffer[i][j];
			}
		}
		output.close();
		return true;
	}
	catch (int e)
	{
		return false;
	}
	
}

Camera::~Camera()
{
	for (int i = 0; i < screenHeight; i++)
	{
		delete[] buffer[i];
	}
	delete[] buffer;
}

Camera::Camera(const Camera& c)
{
	this->operator=(c);
}

Camera& Camera::operator=(const Camera& c)
{
	screenHeight = c.screenHeight;
	screenWidth = c.screenWidth;
	horizontalFov = c.horizontalFov;
	verticalFov = c.verticalFov;
	buffer = c.buffer;
	focalLength = c.focalLength;
	heightFactor = c.heightFactor;
	pos = Vector(c.pos);
	rot = Vector(c.rot);

	return *this;
}