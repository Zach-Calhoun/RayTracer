#include "Vector.h"
#include <math.h>
Vector::Vector()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector::Vector(double a, double b, double c)
{
	x = a;
	y = b;
	z = c;
}

Vector::Vector(Vector& c)
{
	x = c.x;
	y = c.y;
	z = c.z;
}

double Vector::length()
{
	return sqrt(x*x + y*y + z*z);
}

double Vector::dist(Vector v)
{
	double dx = x - v.x;
	double dy = y - v.y;
	double dz = z - v.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

double Vector::dist(Vector u, Vector v)
{
	double dx = u.x - v.x;
	double dy = u.y - v.y;
	double dz = u.z - v.z;
	return sqrt(dx*dx + dy*dy + dz*dz);
}

Vector Vector::operator+(Vector v)
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(Vector v)
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator-()
{
	return Vector(-x, -y, -z);
}

Vector Vector::operator*(double v)
{
	return Vector(x*v, y*v, z*v);
}

double Vector::operator*(Vector v)
{
	return x*v.x + y*v.y + z * v.z;
	//return Vector(x*v.x, y*v.y, z*v.z);
}

double Vector::dot(Vector u, Vector v)
{
	return u.x * v.x + u.y * v.y + u.z * v.z;
}

Vector Vector::cross(Vector v)
{
	double cx = y*v.z - z*v.y;
	double cy = x*v.z - z*v.x;
	double cz = x*v.y - y*v.z;
	return Vector(cx, cy, cz);
}

Vector Vector::cross(Vector u, Vector v)
{
	double cx = u.y*v.z - u.z*v.y;
	double cy = u.x*v.z - u.z*v.x;
	double cz = u.x*v.y - u.y*v.z;
	return Vector(cx, cy, cz);
}



Vector Vector::normalized()
{
	double len = sqrt(x*x + y*y + z*z);
	if (len == 0) {
		std::cout << "Warning, attempted to normalize 0 len vector";
		return Vector();
	}
	return Vector(x / len, y / len, z / len);
}

Vector Vector::normalize()
{
	Vector v = this->normalized();
	x = v.x;
	y = v.y;
	z = v.z;
}

