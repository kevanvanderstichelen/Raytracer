#include "pch.h"
#include "PointLight.h"
#include "Material.h"
PointLight::PointLight(const FPoint3& pos, const RGBColor& color, float intensity)
	:m_Position{ pos }
	,m_Color{ color }
	,m_Intensity{ intensity } 
	,m_CurrentState { true }
{
}

const RGBColor PointLight::GetBiradianceBRDF(const FVector3& ray, const HitRecord& hitrecord) const
{
	if (!m_CurrentState) return {};

	float sqrDistance = SqrDistance(m_Position, hitrecord.hitPoint);
	const RGBColor eRgb = m_Color * (m_Intensity / sqrDistance);

	switch (m_ToggleERGB)
	{
	case ToggleLight::BRDF:
		return RGBColor{ hitrecord.material->Shade(hitrecord, GetDirection(hitrecord), ray) };
		break;
	case ToggleLight::Irradiance:
		return RGBColor{ eRgb };
		break;
	case ToggleLight::IrradianceBRDF:
		return RGBColor{ eRgb * hitrecord.material->Shade(hitrecord, GetDirection(hitrecord), ray) };
		break;
	}
	return {};
}

const FVector3 PointLight::GetDirection(const HitRecord& hitrecord) const
{
	return GetNormalized(m_Position - hitrecord.hitPoint);
}

const FPoint3 PointLight::GetPosition() const
{
	return m_Position;
}

void PointLight::SetState()
{
	m_CurrentState = !m_CurrentState;
}
