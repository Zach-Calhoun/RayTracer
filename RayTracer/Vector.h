#pragma once
#include "stdafx.h"
class Vector 
{
public:
	double x, y, z;
	Vector();
	Vector(double a,double b,double c);
	Vector(Vector& c);

	Vector operator - (Vector v);
	Vector operator-();
	Vector operator + (Vector v);
	double operator * (Vector v);
	static double dot(Vector u, Vector v);
	Vector operator * (double v);
	Vector cross(Vector v);
	static Vector cross(Vector u, Vector v);
	
	double length();
	double dist(Vector v);
	static double dist(Vector u, Vector v);
	Vector normalize();
	Vector normalized();
};