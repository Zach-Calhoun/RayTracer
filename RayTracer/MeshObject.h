#pragma once
#include "Mesh.h"

//inherit sphere because early escape logic will be based on sphere tracing
class MeshObject : public Sphere
{
private:
	Mesh * originalMesh;
	Mesh * transformedMesh;
	Matrix transform;
	Vector pos;
	Vector rot;

	void ApplyTransformation();
public:
	MeshObject();
	MeshObject(Mesh& meshData, Material* m = new Material(Vector(0.5,0.5,0.5)));
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