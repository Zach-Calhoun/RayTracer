#include "Shader.h"
#include "config.h"
Vector Shader::CalculateShading(Intersection& hit, Ray& view, Scene* scene, int renderMode, int& depth)
{
	//calculate each light's contibution
	Vector finalColor = hit.matInfo.diffuse;
	Vector curentColor = hit.matInfo.diffuse;
	if (renderMode & REFLECTIONS && hit.matInfo.roughness < 1 - DBL_EPSILON)
	{
		depth++;
		if (depth > MAX_REFLECTION_DEPTH)
		{
			return Vector(0.9, 0.9, 0.9);
		}

		Vector reflectionDir = view.direction - ((hit.normal*(view.direction*hit.normal)) * 2);
		Ray reflectionRay = Ray(hit.hit, reflectionDir);
		Intersection reflectionResult = reflectionRay.TraceObjects(scene->objects);
		Vector reflColor;
		if (!reflectionResult.success)
		{
			reflColor = Vector(0.9, 0.9, 0.9);
		}
		else
		{
			reflColor = CalculateShading(reflectionResult, reflectionRay, scene, renderMode, depth);
		}
		
		curentColor = (hit.matInfo.diffuse * hit.matInfo.roughness) + (reflColor * (1 - hit.matInfo.roughness));
		 
 
	}

	if (renderMode & DIFFUSE)
	{
		finalColor = Vector();
		//double diffuseIntensity = 0;
		for (int lightIndex = 0; lightIndex < scene->lights.size(); lightIndex++)
		{
			PointLight* light = &scene->lights[0];
			double lightDiffuseIntensity = 0;
			Vector lightDir = (light->pos - hit.hit);
			double lightDistance = lightDir.length();

			double dot = lightDir.normalized() * hit.normal;
			lightDiffuseIntensity = dot;

			if (renderMode & SHADOWS)
			{
				Ray shadowRay(hit.hit, (light->pos - hit.hit).normalized());
				Intersection shadowHit = shadowRay.TraceLight(scene->objects, *light);
				if (shadowHit.success)
				{
					lightDiffuseIntensity = 0;
				}
			}

			if (lightDiffuseIntensity < AMBIENT_LEVEL)
			{
				lightDiffuseIntensity = AMBIENT_LEVEL;
			}
			double lightDiffusePower = light->energy / (lightDistance * lightDistance);
			//Vector lightDiffuseContribution = hit.matInfo.diffuse.blend(light->color) * lightDiffuseIntensity * lightDiffusePower;
			Vector lightDiffuseContribution = curentColor.blend(light->color) * lightDiffuseIntensity * lightDiffusePower;
			finalColor += lightDiffuseContribution;

			//skip specular if in shade
			if (dot < 0 || lightDiffuseIntensity < AMBIENT_LEVEL+DBL_EPSILON)
			{
				continue;
			}

			if (renderMode & SPECULAR)
			{
				Vector reflector = (lightDir + view.direction).normalized();
				double sharpness = hit.normal * reflector;
				if (hit.matInfo.roughness < 0.1) {
					__nop();
				}
				double shinyness = (1 - hit.matInfo.roughness);
				double specularIntensity = pow(sharpness, shinyness * 50 );
				Vector specularContribution = hit.matInfo.diffuse.blend(light->color) * specularIntensity * (light->energy * shinyness) * (1/ lightDistance);
				finalColor += specularContribution;
			}
			
		}
	}

	return finalColor;
	


	//PointLight* light = &scene->lights[0];
	////calc basic light
	//double intensity = 0;
	//Vector finalColor = hit.matInfo.diffuse;

	//if (renderMode & DIFFUSE)
	//{
	//	Vector lightDir = (light->pos - hit.hit);
	//	double lightDistance = lightDir.length();
	//	//finalColor = hit.color.blend(light.color) * intensity * (light.energy / (lightDistance * lightDistance));
	//	intensity = lightDir.normalized() * hit.normal;
	//	if (renderMode & SHADOWS)
	//	{
	//		Ray shadowRay = Ray(hit.hit, lightDir.normalized());
	//		//add small forward to prevent self collison
	//		shadowRay.origin = shadowRay.origin + (lightDir.normalized() * 0.0001);
	//		Intersection shadowHit = Intersection();
	//		for (int l = 0; l < objects.size(); l++)
	//		{
	//			shadowHit = shadowRay.Trace(*objects[l]);
	//			if (shadowHit.success && (shadowRay.origin.dist(shadowHit.hit)) < lightDistance)
	//			{
	//				break;
	//			}
	//		}


	//		if (shadowHit.success && (shadowRay.origin.dist(shadowHit.hit)) < lightDistance)
	//		{
	//			intensity = AMBIENT_LEVEL;
	//		}

	//	}

	//	if (intensity < AMBIENT_LEVEL)
	//	{
	//		intensity = AMBIENT_LEVEL;
	//	}
	//	finalColor = hit.matInfo.diffuse.blend(light->color) * intensity * (light->energy / (lightDistance * lightDistance));

	//}
}
