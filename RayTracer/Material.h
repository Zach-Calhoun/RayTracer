#pragma once
#include "Vector.h"

struct MaterialInfo
{
	Vector diffuse;
	Vector specular;
	double roughness;
};

class Material
{
private:
	Vector diffuse;
	Vector specular;
	double roughness;
	
public:
	//Material();
	Material(Vector dif = Vector(0.5,0.5,0.5), Vector spec = Vector(1,1,1), double rough = 1);
	virtual MaterialInfo GetMatInfo();
	virtual MaterialInfo GetMatInfo(int x, int y);
	virtual Vector GetDiffuse();
	virtual Vector GetSpecular();
};

class OpaqueTiles : public Material
{
	int h, w;
	double roughness;
	Vector color1, color2;
	Vector specular;
public:

	OpaqueTiles(int h, int w, Vector c1, Vector c2, double roughness);
	virtual MaterialInfo GetMatInfo(int x, int y);

};

//
//class MaterialSolid : public Material
//{
//	Vector GetDiffuse();
//	Vector GetSpecular();
//};