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
	verticalFov = (V_FOV / 180) * M_PI;
	horizontalFov = (H_FOV / 180) * M_PI;
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
	double beta = (2 * M_PI - horizontalFov) / 2;
	focalLength = sqrt(halfWidth * (cos(beta) - 1));
	double halfVFovCos = cos(verticalFov / 2);
	double vFovFactor = 1 / (halfVFovCos * halfVFovCos);
	double allowedHeight = (focalLength * focalLength) * (vFovFactor - 1);
	heightFactor = screenHeight / allowedHeight;
}

Ray Camera::GenerateRay(int y, int x)
{
	//get relative pos in camera space
	//after some drawings on a piece of paper
	int cam_x = x - (screenWidth / 2);
	int cam_y = y - (screenHeight / 2);
	int ray_y = (y / screenHeight) * heightFactor;

	Vector dir = Vector(cam_x, ray_y, focalLength);
	Ray ray = Ray(pos, dir.normalized());
	

	

	//TODO: Apply camera rotation to generated vector

}