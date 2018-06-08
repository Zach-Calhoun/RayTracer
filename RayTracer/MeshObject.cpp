#include "MeshObject.h"

MeshObject::MeshObject()
{
	originalMesh = NULL;
	transformedMesh = NULL;
	transform = Matrix::Identity();
}

MeshObject::MeshObject(Mesh& meshData, Material* m)
{
	mat = m;
	transform = Matrix::Identity();
	SetMesh(meshData);
}

MeshObject::~MeshObject()
{
	transform.Release();
	//delete originalMesh;
	delete transformedMesh;
}
void MeshObject::SetMesh(Mesh& meshData)
{
	//mesh = &meshData;
	originalMesh = &meshData;
	transformedMesh = new Mesh(meshData);
	radius = transformedMesh->getRadius();
	ApplyTransformation();
}

void MeshObject::SetPos(double x, double y, double z)
{
	SetPos(Vector(x, y, z));
}

void MeshObject::SetRot(double x, double y, double z)
{
	SetRot(Vector(x, y, z));
}

void MeshObject::SetPos(Vector p)
{
	pos = p;
	origin = p;
	ApplyTransformation();
}

void MeshObject::SetRot(Vector r)
{
	rot = r;
	ApplyTransformation();

}

void MeshObject::ApplyTransformation()
{
	transform.Release();
	transform = Matrix::Identity();

	Matrix translation = Matrix::Translation(pos);
	Matrix rotation = Matrix::Rotation(rot);

	//transform = rotation * transform;
	transform = translation * rotation;

	translation.Release();
	rotation.Release();

	transformedMesh->ApplyTransformation(originalMesh, transform);
}

Vector MeshObject::GetPos()
{
	return pos;
}

Vector MeshObject::GetRot()
{
	return rot;
}

Intersection MeshObject::Trace(Ray& r)
{
	Intersection initialTest = Sphere::Trace(r);
	if (initialTest.success)
	{
		//go deeper
		double u, v;
		Intersection result = transformedMesh->Trace(r, transform,u,v);
		//transform mesh
		result.matInfo = mat->GetMatInfo(u*10,v*10);
		return result;
		//cast tris
	}
	else 
	{
		//faild basic radius check
		return initialTest;
	}
}