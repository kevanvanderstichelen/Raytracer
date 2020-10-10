#include "pch.h"
#include "Plane.h"

Plane::Plane(const FPoint3& origin, const Material* material, const FVector3& normal)
	:Object{ material }
	, m_Origin{ origin }
	, m_Normal{ normal }
{
}

bool Plane::Hit(const Ray& ray, HitRecord& hitRecord) const
{
	const float t = Dot((m_Origin - ray.origin), m_Normal) / Dot(ray.direction, m_Normal);
	if (t > ray.tMin && t < ray.tMax)
	{
		hitRecord.tValue = t;
		hitRecord.hitPoint = ray.origin + ray.direction * hitRecord.tValue;
		hitRecord.material = m_Material;
		hitRecord.normal = m_Normal;
		return true;
	}
	return false;
}

void Plane::Update(float elapsedSec)
{
}
