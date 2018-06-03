#pragma once
#include "Primitives.h"
#include "Mesh.h"

//inherit sphere because early escape logic will be based on sphere tracing
class MeshObject : public Sphere
{
private:
	Mesh * mesh;
	Matrix transform;
	Vector pos;
	Vector rot;
public:
	MeshObject();
	MeshObject(Mesh& meshData);
	~MeshObject();

	void SetMesh(Mesh& meshData);
	void SetRot(Vector r);
	void SetPos(Vector p);
	void SetPos(double x, double y, double z);
	void SetRot(double x, double y, double z);
	Vector GetPos();
	Vector GetRot();

	Intersection Trace(Ray& r);

};