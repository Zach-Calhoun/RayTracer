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

MaterialInfo Material::GetMatInfo()
{
	MaterialInfo res;
	res.diffuse = diffuse;
	res.specular = specular;
	res.roughness = roughness;

	return res;
}
