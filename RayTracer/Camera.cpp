#include "Primitives.h"
#include "config.h"
#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera()
{
	pos = Vector();
	rot = Vector();

	screenHeight = SCREEN_HEIGHT;
	screenWidth = SCREEN_WIDTH;
	verticalFov = ((double)V_FOV / 180) * M_PI;
	horizontalFov = ((double)H_FOV / 180) * M_PI;
	CalculateRayConstants();
}

void Camera::Setup(int h, int w, double v_fov, double h_fov)
{
	screenHeight = h;
	screenWidth = w;
	verticalFov = (v_fov / 180) * M_PI;
	horizontalFov = (h_fov / 180) * M_PI;
	CalculateRayConstants();
}

void Camera::CalculateRayConstants()
{
	//after some drawings on a piece of paper
	int halfWidth = screenWidth / 2;
	double beta = (M_PI - horizontalFov) / 2;
	double cosBeta = cos(beta);
	focalLength = sqrt(halfWidth * halfWidth * (1 / (cosBeta * cosBeta) - 1));
	double halfVFovCos = cos(verticalFov / 2);
	double vFovFactor = 1 / (halfVFovCos * halfVFovCos);
	double allowedHeight = 2 * sqrt((focalLength * focalLength) * (vFovFactor - 1));
	heightFactor = screenHeight / allowedHeight;
}

Ray Camera::GenerateRay(int y, int x)
{
	//get relative pos in camera space
	//after some drawings on a piece of paper
	int cam_x = x - (screenWidth / 2);
	int ray_y = ((double)y / screenHeight) * heightFactor;
	int cam_y = ((screenHeight * heightFactor) / 2) - y;

	Vector dir = Vector(cam_x, cam_y, focalLength);
	Ray ray = Ray(pos, dir.normalized());
	
	return ray;
	//TODO: Apply camera rotation to generated vector

}

void Camera::LookAt(Vector v)
{

}