#pragma once
#include "Vector.h"
#include "Matrix.h"
class Camera
{
private:
	int screenWidth;
	int screenHeight;
	double horizontalFov;
	double verticalFov;
	Vector ** buffer;


	//distance between "lens" and "origin"
	double focalLength;
	//scaling fdactor between screen height and allowed height from vertical FOV calcluations
	double heightFactor;

	void CalculateRayConstants();

public:
	Vector pos;
	Vector rot;

	Matrix transform;


	Camera();
	Camera(int h, int w, double v_fov, double h_fov);
	Camera(const Camera& c);
	Camera& operator = (const Camera& c);

	int getWidth() const;
	int getHeight() const;


	void Setup(int h, int w, double h_fov, double v_fov);
	void LookAt(Vector v);
	void SetRotation(double x, double y, double z);
	void SetRotation(Vector r);
	//returns the coresponding ray for x and y screen coordinates;
	Ray GenerateRay(int x, int y);

	//void Render(Scene& scene);
	//void RenderPart(Scene& scene, int topY, int topX, int botY, int botX);
	//void Render(Scene& scene, int frame);
	bool SavePpm(char * path);
	bool SavePpm(char * path, int frame);
	friend class SDLCameraRenderer;
	friend class Renderer;
	~Camera();
};
