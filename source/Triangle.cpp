#include "pch.h"
#include "Triangle.h"

Triangle::Triangle(const FPoint3& pos, const FVector3& v0, const FVector3& v1, const FVector3& v2, const Material* material, const Culling& culling)
	:Object{ material }
	, m_RotationRatio { 0.5f }
	, m_V0{ pos + v0 }
	, m_V1{ pos + v1 }
	, m_V2{ pos + v2 }
	, m_Normal{ GetNormalized(Cross(m_V1 - m_V0, m_V2 - m_V0)) }
	, m_Center{ (m_V0 + m_V1 + m_V2) / 3.f }
	, m_Culling{ culling }
	, m_Matrix{ m_Matrix.Identity() }
	, m_Position{ pos }
{

}

bool Triangle::Hit(const Ray& ray, HitRecord& hitrecord) const
{
	if (Dot(ray.direction, m_Normal) == 0.f) return false;
	const FVector3 L = m_Center - FVector3(ray.origin);
	float t = Dot(L, m_Normal) / Dot(ray.direction, m_Normal);
	if (t < ray.tMin || t > ray.tMax) return false;

	const FPoint3 p = ray.origin + ray.direction * t;

	FVector3 edge = m_V1 - m_V0;
	FVector3 pointToSide = FVector3(p) - m_V0;
	if (Dot(m_Normal, Cross(edge, pointToSide)) < 0.f) return false;

	edge = m_V2 - m_V1;
	pointToSide = FVector3(p) - m_V1;
	if (Dot(m_Normal, Cross(edge, pointToSide)) < 0.f) return false;

	edge = m_V0 - m_V2;
	pointToSide = FVector3(p) - m_V2;
	if (Dot(m_Normal, Cross(edge, pointToSide)) < 0.f) return false;

	switch (m_Culling)
	{
	case Front:
		//if ray isn't the original tMax value -> means shadow ray (opposite culling)
		if (ray.tMax < FLT_MAX) { if (Dot(ray.direction, m_Normal) > 0.f) return false; }
		else { if (Dot(ray.direction, m_Normal) < 0.f) return false; }
		break;
	case Back:
		if (ray.tMax < FLT_MAX) { if (Dot(ray.direction, m_Normal) < 0.f) return false; }
		else { if (Dot(ray.direction, m_Normal) > 0.f) return false; }
		break;
	case None:
		break;
	}

	hitrecord.hitPoint = p;
	hitrecord.normal = m_Normal;
	hitrecord.material = m_Material;
	hitrecord.tValue = t;


	return true;

}

void Triangle::Update(float elapsedSec)
{
	FMatrix3 rotation = MakeRotationY(m_RotationRatio * elapsedSec);
	m_V0 = (rotation * (m_V0 - m_Position)) + m_Position;
	m_V1 = (rotation * (m_V1 - m_Position)) + m_Position;
	m_V2 = (rotation * (m_V2 - m_Position)) + m_Position;
	m_Normal = { GetNormalized(Cross(m_V1 - m_V0, m_V2 - m_V0)) };
}
