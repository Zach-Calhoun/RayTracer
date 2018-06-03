#include "Matrix.h"
#include "Vector.h"
#include <iostream>
Matrix::Matrix()
{
	Matrix(4, 4);
}

Matrix::Matrix(int m, int n)
{
	this->m = m;
	this->n = n;
	_mat = new double*[m];
	for (int i = 0; i < m; i ++ )
	{
		_mat[i] = new double[n];
	}
}

double* Matrix::operator[](int i)
{
	return _mat[i];
}

Matrix Matrix::operator*(const Matrix& mat)
{
	if (n != mat.m)
		throw - 1;

	Matrix result = Matrix(m, mat.n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < mat.n; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < mat.m; k++)
			{
				result[i][j] += _mat[i][k] * mat._mat[k][j];
			}
		}
	}
	return result;
}

Vector Matrix::operator*(const Vector& v)
{
	Matrix tmp = Matrix(4, 1);
	tmp[0][0] = v.x;
	tmp[1][0] = v.y;
	tmp[2][0] = v.z;
	tmp[3][0] = 1;
	//std::cout << tmp;
	//std::cout << *this;
	Matrix res = (*this)*tmp;
	//std::cout << res;
	tmp.Release();
	Vector result = Vector(res[0][0], res[1][0], res[2][0]);
	res.Release();
	return result;
}

Matrix Matrix::Identity()
{
	Matrix mat = Matrix(4, 4);
	mat.SetIdentity();
	return mat;
	
}

Matrix& Matrix::SetIdentity()
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == j)
			{
				_mat[i][j] = 1;
			}
			else
			{
				_mat[i][j] = 0;
			}

		}
	}
	return *this;
}



Matrix& Matrix::rotateX(double ang)
{
	Matrix rot = Matrix::RotationX(ang);
	*this = rot * (*this);
	rot.Release();
	return *this;
}

Matrix Matrix::RotationX(double ang)
{
	Matrix rot = Matrix::Identity();
	rot[1][1] = cos(ang);
	rot[1][2] = -sin(ang);
	rot[2][1] = sin(ang);
	rot[2][2] = cos(ang);
	return rot;
}

Matrix& Matrix::rotateY(double ang)
{
	Matrix rot = Matrix::RotationY(ang);
	*this = rot * (*this);
	rot.Release();
	return *this;
}

Matrix Matrix::RotationY(double ang)
{
	Matrix rot = Matrix::Identity();
	rot[0][0] = cos(ang);
	rot[0][2] = sin(ang);
	rot[2][0] = -sin(ang);
	rot[2][2] = cos(ang);
	return rot;
}

Matrix& Matrix::rotateZ(double ang)
{
	Matrix rot = Matrix::RotationZ(ang);
	*this = rot * (*this);
	rot.Release();
	return *this;
}

Matrix Matrix::RotationZ(double ang)
{
	Matrix rot = Matrix::Identity();
	rot[0][0] = cos(ang);
	rot[0][1] = -sin(ang);
	rot[1][0] = sin(ang);
	rot[1][1] = cos(ang);
	return rot;
}



Matrix Matrix::Rotation(Vector r)
{
	return Matrix::Rotation(r.x, r.y, r.z);
}

Matrix Matrix::Rotation(double x, double y, double z)
{
	Matrix newRot = Matrix::Identity();
	newRot.rotateX(x);
	newRot.rotateY(y);
	newRot.rotateZ(z);
	return newRot;
}

Matrix& Matrix::rotate(Vector r)
{
	return rotate(r.x, r.y,r.z);
}

Matrix& Matrix::rotate(double x, double y, double z)
{
	Matrix rot = Matrix::Rotation(x, y, z);
	*this = rot * (*this);
	rot.Release();
	return *this;
}

Matrix Matrix::TranslationX(double deltaX)
{
	Matrix tran = Matrix::Identity();
	tran[0][3] = deltaX;
	return tran;
}

Matrix& Matrix::translateX(double t)
{
	Matrix tran = Matrix::TranslationX(t);
	*this = tran * (*this);
	tran.Release();
	return *this;
}

Matrix Matrix::TranslationY(double deltaY)
{
	Matrix tran = Matrix::Identity();
	tran[1][3] = deltaY;
	return tran;
}

Matrix& Matrix::translateY(double t)
{
	Matrix tran = Matrix::Identity();
	*this = tran * (*this);
	tran.Release();
	return *this;
}

Matrix Matrix::TranslationZ(double deltaZ)
{
	Matrix tran = Matrix::Identity();
	tran[3][3] = deltaZ;
	return tran;
}

Matrix& Matrix::translateZ(double t)
{
	Matrix tran = Matrix::Identity();
	*this = tran * (*this);
	tran.Release();
	return *this;
}

Matrix Matrix::Translation(Vector p)
{
	return Matrix::Translation(p.x, p.y, p.z);
}

Matrix Matrix::Translation(double x, double y, double z)
{
	Matrix newT = Matrix::Identity();
	newT[0][3] = x;
	newT[1][3] = y;
	newT[2][3] = z;
	return newT;
}

Matrix& Matrix::translate(Vector p)
{
	return translate(p.x, p.y, p.z);
}

Matrix& Matrix::translate(double x, double y, double z)
{
	Matrix tran = Matrix::Translation(x, y, z);
	*this = tran * (*this);
	tran.Release();
	return *this;
}


void Matrix::Release()
{
	for (int i = 0; i < m; i++)
	{
		delete[] _mat[i];
	}
	delete[] _mat;
}

Vector Matrix::AsVector()
{
	return Vector(_mat[0][0], _mat[1][0], _mat[2][0]);
}

std::ofstream& operator<< (std::ofstream& o,Matrix&  m)
{
	for (int i = 0; i < m.m; i++)
	{
		for (int j = 0; j < m.n; j++)
		{
			o << m[i][j] << "\t";
		}
		o << std::endl;
	}
	return o;
}

std::ostream& operator<< (std::ostream& o, Matrix&  m)
{
	for (int i = 0; i < m.m; i++)
	{
		for (int j = 0; j < m.n; j++)
		{
			o << m[i][j] << "\t";
		}
		o << std::endl;
	}
	return o;
}