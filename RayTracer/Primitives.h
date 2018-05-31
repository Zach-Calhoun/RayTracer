#pragma once
#include "Vector.h"
#include "Matrix.h"
//#include <stdlib.h>
//#include 
class Ray;
class Scene;

class Intersection
{
public:
	Vector hit;
	Vector color;
	Vector normal;
	bool success;


	Intersection();
};

class RayTraceable
{
public:
	virtual Intersection Trace(Ray& r) = 0;
};

class Ray
{
public:
	Vector origin;
	Vector direction;

	Ray();
	Ray(Vector o, Vector d);
	Intersection Trace(RayTraceable& o);
};

class Camera
{
private:
	int screenWidth;
	int screenHeight;
	double horizontalFov;
	double verticalFov;
	Vector ** buffer;
	Matrix transform;
	//distance between "lens" and "origin"
	double focalLength;
	//scaling fdactor between screen height and allowed height from vertical FOV calcluations
	double heightFactor;

	void CalculateRayConstants();

public:
	Vector pos;
	Vector rot;

	Camera();
	Camera(int h, int w, double v_fov, double h_fov);
	Camera(const Camera& c);
	Camera& operator = (const Camera& c);

	
	
	void Setup(int h, int w, double h_fov, double v_fov);
	void LookAt(Vector v);
	//returns the coresponding ray for x and y screen coordinates;
	Ray GenerateRay(int x, int y);

	void Render(Scene& scene);
	bool SavePpm(char * path);

	~Camera();
};



//eventualy theese will contain a material type object
class Sphere : public RayTraceable
{
public:
	Vector origin;
	double radius;
	Vector color;
	

	Sphere();
	Sphere(Vector o, double r, Vector c);
	Intersection Trace(Ray& r);

};

class Plane : public RayTraceable
{
public:
	Vector normal;
	double distance;
	Vector color;

	Plane();
	Plane(Vector n, double d, Vector c);
	Intersection Trace(Ray& r);
};
