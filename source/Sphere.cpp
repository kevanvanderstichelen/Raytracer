#include "pch.h"
#include "Sphere.h"

Sphere::Sphere(const FPoint3& origin, const Material* material, const float radius)
	:Object{ material }
	,m_Origin{ origin }
	,m_Radius{ radius }
{
}

bool Sphere::Hit(const Ray& ray, HitRecord& hitRecord) const
{
	float a, b, c, d;
	const FVector3 oc = ray.origin - m_Origin;
	a = Dot(ray.direction, ray.direction);
	b = Dot(2 * ray.direction, oc);
	c = Dot(oc, oc) - (m_Radius * m_Radius);
	d = b * b - 4 * a * c;

	if (d < 0)
	{
		return false;
	}

	float t = ((-b) - sqrtf(d)) / (2.f * a);

	if (t > ray.tMin && t < ray.tMax )
	{

		if (t < ray.tMin)
		{
			t = ((-b) + sqrtf(d)) / (2.f * a);
		}

		hitRecord.tValue = t;
		hitRecord.hitPoint = ray.origin + ray.direction * hitRecord.tValue;
		hitRecord.material = m_Material;
		hitRecord.normal = hitRecord.hitPoint - m_Origin;
		return true;
	}

	return false;
}

void Sphere::Update(float elapsedSec)
{
}
