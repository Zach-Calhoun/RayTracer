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
	virtual Vector GetDiffuse();
	virtual Vector GetSpecular();
};

//
//class MaterialSolid : public Material
//{
//	Vector GetDiffuse();
//	Vector GetSpecular();
//};