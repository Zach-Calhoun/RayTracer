#include "MeshObject.h"

MeshObject::MeshObject()
{
	mesh = NULL;
	transform = Matrix::Identity();
}

MeshObject::MeshObject(Mesh& meshData)
{
	transform = Matrix::Identity();
	SetMesh(meshData);
}

MeshObject::~MeshObject()
{
	transform.Release();
}
void MeshObject::SetMesh(Mesh& meshData)
{
	mesh = &meshData;
	radius = mesh->getRadius();
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
	//rot then pos;
	transform.Release();
	transform = Matrix::Identity();

	Matrix translation = Matrix::Translation(pos);
	Matrix rotation = Matrix::Rotation(rot);
	

	transform = rotation * translation;

	translation.Release();
	rotation.Release();
}

void MeshObject::SetRot(Vector r)
{
	rot = r;
	transform.Release();
	transform = Matrix::Identity();

	Matrix translation = Matrix::Translation(pos);
	Matrix rotation = Matrix::Rotation(rot);
	
	transform = rotation * translation;

	translation.Release();
	rotation.Release();

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
		Intersection result = mesh->Trace(r, transform);
		//transform mesh
		result.color = color;
		return result;
		//cast tris
	}
	else 
	{
		//faild basic radius check
		return initialTest;
	}
}