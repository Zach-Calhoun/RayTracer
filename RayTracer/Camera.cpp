
#include "Camera.h"
#include "Scene.h"
#include "config.h"
#define _USE_MATH_DEFINES
#define _USE_CRT_NO_WARNINGS
#include <math.h>
#include <vector>

Camera::Camera()
{
	pos = Vector();
	rot = Vector();
	transform = Matrix::Identity();

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

	SetRotation(rot);

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

int Camera::getHeight() const{
	return screenHeight;
}

int Camera::getWidth() const {
	return screenWidth;
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
	//rotate dir;
	ray.direction = transform * ray.direction;
	
	return ray;
	//TODO: Apply camera rotation to generated vector

}

void Camera::LookAt(Vector v)
{

}

void Camera::SetRotation(double x, double y, double z)
{
	SetRotation(Vector(x, y, z));
	
	

}

void Camera::SetRotation(Vector r)
{
	rot = r;
	transform = Matrix::Identity();
	transform.rotateX(rot.x);
	transform.rotateY(rot.y);
	transform.rotateZ(rot.z);
}
//
//void Camera::Render(Scene& scene)
//{
//	
//
//}
//
//void Camera::RenderPart(Scene& scene, int topY, int topX, int botY, int botX)
//{
//
//}

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

bool Camera::SavePpm(char * path, int frame)
{
	try
	{
		std::string fullName = path;
		fullName.append("_");
		static char cbufr[6];
		fullName.append(_itoa(frame, cbufr, 10));
		fullName.append(".ppm");
		std::ofstream output = std::ofstream(fullName);

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
		std::cout << e << std::endl;
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