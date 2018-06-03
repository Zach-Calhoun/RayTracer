#include "Mesh.h"
#include <fstream>

Mesh::Mesh()
{
	
}

Mesh::Mesh(char* path)
{
	LoadData(path);
}

Mesh::Mesh(int numVerts, int numFaces, Vector* verts, int* faces)
{
	SetData(numVerts, numFaces, verts, faces);
}

double Mesh::getRadius()
{
	return boundingSphereRadius;
}
void Mesh::LoadData(char * path)
{
	CalcNormals();
	CalculateRadius();
}

void Mesh::SetData(int numVerts, int numFaces, Vector * verts, int* faces)
{
	CalcNormals();
	CalculateRadius();
}

void Mesh::InitCube()
{
	numVertices = 8;
	vertices = new Vector[numVertices];
	numTris = 6 * 2;
	faceIndices = new int[numTris*vertsPerFace];

	vertices[0] = Vector(-0.5, 0.5, -0.5);
	vertices[1] = Vector(0.5, 0.5, -0.5);
	vertices[2] = Vector(0.5, 0.5, 0.5);
	vertices[3] = Vector(-0.5, 0.5, 0.5);
	vertices[4] = Vector(-0.5, -0.5, -0.5);
	vertices[5] = Vector(0.5, -0.5, -0.5);
	vertices[6] = Vector(0.5, -0.5, 0.5);
	vertices[7] = Vector(-0.5, -0.5, 0.5);
	
	faceIndices[0] = 0;
	faceIndices[1] = 1;
	faceIndices[2] = 2;
	faceIndices[3] = 2;
	faceIndices[4] = 3;
	faceIndices[5] = 1;

	faceIndices[6] = 2;
	faceIndices[7] = 1;
	faceIndices[8] = 5;
	faceIndices[9] = 2;
	faceIndices[10] = 5;
	faceIndices[11] = 6;

	faceIndices[12] = 2;
	faceIndices[13] = 3;
	faceIndices[14] = 6;
	faceIndices[15] = 6;
	faceIndices[16] = 3;
	faceIndices[17] = 1;

	faceIndices[18] = 3;
	faceIndices[19] = 0;
	faceIndices[20] = 4;
	faceIndices[21] = 3;
	faceIndices[22] = 4;
	faceIndices[23] = 7;

	faceIndices[24] = 0;
	faceIndices[25] = 4;
	faceIndices[26] = 1;
	faceIndices[27] = 1;
	faceIndices[28] = 4;
	faceIndices[29] = 5;

	faceIndices[30] = 5;
	faceIndices[31] = 4;
	faceIndices[32] = 7;
	faceIndices[33] = 5;
	faceIndices[34] = 7;
	faceIndices[35] = 6;

	CalcNormals();
	CalculateRadius();
}

void Mesh::CalcNormals()
{
	normals = new Vector[numTris];
	for (int i = 0; i < numTris; i++)
	{
		normals[i] = (vertices[i*vertsPerFace + 1] - vertices[i*vertsPerFace]).cross((vertices[i*vertsPerFace + 2] - vertices[i*vertsPerFace]));
	}
}

void Mesh::CalculateRadius()
{
	Vector centerOfGravity;
	for (int i = 0; i < numVertices; i++)
	{
		centerOfGravity += vertices[i];
	}
	centerOfGravity = centerOfGravity * (1.0 / numVertices);

	//center mesh and calc max dist between cog and verts
	double maxDist = 0;
	for (int i = 0; i < numVertices; i ++)
	{
		vertices[i] = vertices[i] - centerOfGravity;
		if (vertices[i].length() > maxDist)
		{
			maxDist = vertices[i].length();
		}
	}
	boundingSphereRadius = maxDist;
	
}

Intersection Mesh::Trace(Ray& ray, Matrix& transform)
{
	//iterate over all traingles and return the shortes length
	Intersection result;
	double minDist = INFINITY;

	for (int i = 0; i < numTris; i++)
	{
		Intersection tmpHit;
		//TODO Cache some of theese
		Matrix normDir = normals[i].AsDirection();
		Matrix transformedNormal = transform * normDir;
		//normDir.Release();
		Vector normal = transformedNormal.AsVector();

		if (normal * ray.direction > 0)
		{
			//this is a backface;
			continue;
		}
		else
		{
			//possible collision
			int vOffset = i * vertsPerFace;
			Vector v1 = vertices[vOffset];
			Vector v2 = vertices[vOffset + 1];
			Vector v3 = vertices[vOffset + 2];
			Vector edge1, edge2, h, s, q;
			double a, f, u, v;
			edge1 = v2 - v1;
			edge2 = v3 - v1;
			h = ray.direction.cross(edge2);
			a = edge1 * h;
			if (a > -DBL_EPSILON && a < DBL_EPSILON)
			{
				//no hit
				continue;
			}
			f = 1.0 / a;
			s = ray.origin - v1;
			u = f * (s * h);
			if (u < 0 || u > 1)
			{
				continue;
			}
			q = s.cross(edge1);
			v = f * (ray.direction * q);
			if (v < 0 || u + v > 1)
			{
				continue;
			}
			double t = f * (edge2 * q);
			if (t > DBL_EPSILON)
			{
				tmpHit.hit = ray.origin + (ray.direction * t);
				tmpHit.success = true;
				tmpHit.normal = normal;
				//handle color?
				if (ray.origin.dist(tmpHit.hit) < minDist)
				{
					result = tmpHit;
				}
			}
			else
			{
				continue;
			}
		}
	}

	return result;
}

void Mesh::Clear()
{
	delete[] vertices;
	delete[] faceIndices;
	delete[] normals;
}

Mesh::~Mesh()
{
	Clear();
}


