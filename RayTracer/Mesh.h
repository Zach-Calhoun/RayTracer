#pragma once
#include "Vector.h"
#include "Primitives.h"
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

	void SetData(int numVerts, int numFaces, Vector * verts, int* faces);
	void LoadData(char * path);
	void InitCube();
	void Clear();

	double getRadius();
	Intersection Trace(Ray& ray, Matrix& transform);

	~Mesh();
};