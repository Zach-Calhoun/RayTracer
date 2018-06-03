#pragma once
#include <fstream>
#include <iostream>
//#include "Vector.h"
class Vector;

class Matrix
{
private:
	int m, n;
	double ** _mat;
public:
	Matrix();
	Matrix(int m, int n);

	static Matrix Identity();
	Matrix& SetIdentity();

	Matrix operator*(const Matrix& mat) const;
	Vector operator*(const Vector& v);
	double* operator[](int i);
	
	Matrix& rotateX(double ang);
	Matrix& rotateY(double ang);
	Matrix& rotateZ(double ang);
	Matrix& rotate(double x, double y, double z);
	Matrix& rotate(Vector r);

	Matrix& translateX(double t);
	Matrix& translateY(double t);
	Matrix& translateZ(double t);
	Matrix& translate(double x, double y, double z);
	Matrix& translate(Vector p);

	Vector AsVector();

	Matrix& invert();
	void Release();

	static Matrix RotationX(double ang);
	static Matrix RotationY(double ang);
	static Matrix RotationZ(double ang);
	static Matrix Rotation(double x, double y, double z);
	static Matrix Rotation(Vector r);

	

	static Matrix TranslationX(double deltaX);
	static Matrix TranslationY(double deltaY);
	static Matrix TranslationZ(double deltaZ);
	static Matrix Translation(double x, double y, double z);
	static Matrix Translation(Vector p);


	static Matrix ScaleX(double s);
	static Matrix ScaleY(double s);
	static Matrix ScaleZ(double s);
	static Matrix Scale(double s);
	static Matrix Scale(double x, double y, double z);

	static Matrix Inv(Matrix m);
	friend std::ofstream& operator<< (std::ofstream& o, Matrix&  m);
	friend std::ostream& operator<< (std::ostream& o, Matrix&  m);



};