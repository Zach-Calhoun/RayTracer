#pragma once
#include "Vector.h"
#include "Sphere.h"
//reprezents 3d vertex data
class Mesh
{
private:
	static const int vertsPerFace = 3;
	
	Vector* vertices;
	Vector* normals;
	int* faceIndices;
	int numTris;
	int numVertices;
	double boundingSphereRadius;

	void CalcNormals();
	void CalculateRadius();
public:
	Mesh();
	Mesh(char * path);
	Mesh(int numVerts, int numFaces, Vector* verts, int* faces);
	Mesh(const Mesh& m);
	Mesh& operator=(const Mesh& m);

	void ApplyTransformation(const Mesh* reference, const Matrix& t);
	void SetData(int numVerts, int numFaces, Vector * verts, int* faces);
	void LoadData(char * path);
	void InitCube();
	void InitTriangle();
	void Clear();

	double getRadius();
	Intersection Trace(Ray& ray, Matrix& transform, double& u, double& v);

	~Mesh();
};