#include "Matrix.h"

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
				result[i][j] += _mat[i][k] * _mat[k][j];
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
	Matrix res = (*this)*tmp;
	Vector result = Vector(res[0][0], res[1][0], res[2][0]);
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

void Matrix::Release()
{
	for (int i = 0; i < m; i++)
	{
		delete[] _mat[i];
	}
	delete[] _mat;
}