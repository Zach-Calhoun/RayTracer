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

Mesh::Mesh(const Mesh& m)
{
	*this = m;
}

Mesh& Mesh::operator=(const Mesh& m)
{
	numVertices = m.numVertices;
	numTris = m.numTris;
	boundingSphereRadius = m.boundingSphereRadius;
	vertices = new Vector[numVertices];
	faceIndices = new int[numTris*vertsPerFace];
	normals = new Vector[numTris];


	memcpy(vertices, m.vertices, numVertices * sizeof(Vector));
	memcpy(faceIndices, m.faceIndices, numTris*vertsPerFace*sizeof(int));
	memcpy(normals, m.normals, numTris*sizeof(Vector));
	return *this;
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

void Mesh::ApplyTransformation(const Mesh* reference, const Matrix& t)
{
	//rotate normals
	for (int i = 0; i < numTris; i++)
	{
		Matrix normDir = reference->normals[i].AsDirection();
		Matrix transformedNormal = t * normDir;
		normDir.Release();
		normals[i] = transformedNormal.AsVector();
		transformedNormal.Release();
	}
	//transform vertices
	for (int i = 0; i < numVertices; i++)
	{
		Matrix vPos = reference->vertices[i].AsPosition();
		Matrix tVert = t * vPos;
		vPos.Release();
		vertices[i] = tVert.AsVector();
		tVert.Release();
	}
	
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
	faceIndices[1] = 2;
	faceIndices[2] = 1;
	faceIndices[3] = 0;
	faceIndices[4] = 3;
	faceIndices[5] = 2;

	faceIndices[6] = 1;
	faceIndices[7] = 2;
	faceIndices[8] = 6;
	faceIndices[9] = 1;
	faceIndices[10] = 6;
	faceIndices[11] = 5;

	faceIndices[12] = 2;
	faceIndices[13] = 3;
	faceIndices[14] = 6;
	faceIndices[15] = 6;
	faceIndices[16] = 3;
	faceIndices[17] = 7;

	faceIndices[18] = 3;
	faceIndices[19] = 0;
	faceIndices[20] = 7;
	faceIndices[21] = 0;
	faceIndices[22] = 4;
	faceIndices[23] = 7;

	faceIndices[24] = 0;
	faceIndices[25] = 1;
	faceIndices[26] = 4;
	faceIndices[27] = 4;
	faceIndices[28] = 1;
	faceIndices[29] = 5;

	faceIndices[30] = 4;
	faceIndices[31] = 5;
	faceIndices[32] = 7;
	faceIndices[33] = 5;
	faceIndices[34] = 6;
	faceIndices[35] = 7;

	CalcNormals();
	CalculateRadius();
}

void Mesh::InitTriangle()
{
	numVertices = 3;
	vertices = new Vector[numVertices];
	numTris =1;
	faceIndices = new int[numTris*vertsPerFace];

	vertices[0] = Vector(-5, 0, 5);
	vertices[1] = Vector(5,0,5);
	vertices[2] = Vector(-5, 0, -5);

	faceIndices[0] = 0;
	faceIndices[1] = 1;
	faceIndices[2] = 2;


	CalcNormals();
	CalculateRadius();
}

void Mesh::CalcNormals()
{
	normals = new Vector[numTris];
	for (int i = 0; i < numTris; i++)
	{
		int offset = i * vertsPerFace;
		Vector v1 = vertices[faceIndices[offset]];
		Vector v2 = vertices[faceIndices[offset + 1]];
		Vector v3 = vertices[faceIndices[offset + 2]];
		Vector e1 = v2 - v1;
		Vector e2 = v3 - v1;

		normals[i] = e1.cross(e2).normalized();
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
		/*Matrix normDir = normals[i].AsDirection();
		Matrix transformedNormal = transform * normDir;
		normDir.Release();
		Vector normal = transformedNormal.AsVector();*/
		//transformedNormal.Release();
		Vector normal = normals[i];

		if (normal * ray.direction > 0)
		{
			//this is a backface;
			continue;
		}
		else
		{
			//possible collision
			int vOffset = i * vertsPerFace;
			Vector v1 = vertices[faceIndices[vOffset]];
			Vector v2 = vertices[faceIndices[vOffset + 1]];
			Vector v3 = vertices[faceIndices[vOffset + 2]];
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
				double hitDist = ray.origin.dist(tmpHit.hit);
				if (hitDist < minDist)
				{

					minDist = hitDist;
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


