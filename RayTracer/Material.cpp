#include "Material.h"

//Material::Material()
//{
//	
//}

Material::Material(Vector dif, Vector spec, double rough)
{
	diffuse = dif;
	specular = spec;
	roughness = rough;
}

Vector Material::GetDiffuse()
{
	return diffuse;
}

Vector Material::GetSpecular()
{
	return specular;
}

MaterialInfo Material::GetMatInfo(int x, int y)
{
	return GetMatInfo();
}

MaterialInfo Material::GetMatInfo()
{
	MaterialInfo res;
	res.diffuse = diffuse;
	res.specular = specular;
	res.roughness = roughness;

	return res;
}

OpaqueTiles::OpaqueTiles(int h, int w, Vector c1, Vector c2, double roughness)
{
	this->h = h;
	this->w = w;
	color1 = c1;
	color2 = c2;
	this->roughness = roughness;
}

MaterialInfo OpaqueTiles::GetMatInfo(int x, int y)
{
	/*int divx = (x % w) % 2;
	int divy = (y % h) % 2;*/
	int divx = (abs(x) % (2*w)) % 2;
	int divy = (abs(y) % (2*h)) % 2;

	if (divx ^ divy)
	{
		//white
		MaterialInfo result = MaterialInfo();
		result.diffuse = color1;
		result.roughness = roughness;
		result.specular = specular;
		return result;
	}
	else
	{
		//black
		MaterialInfo result = MaterialInfo();
		result.diffuse = color2;
		result.roughness = roughness;
		result.specular = specular;
		return result;
	}
}
