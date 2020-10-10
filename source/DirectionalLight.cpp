#include "pch.h"
#include "DirectionalLight.h"
#include "Material.h"

DirectionalLight::DirectionalLight(const FVector3& normal, const RGBColor& color, float intensity)
	:m_Direction{ GetNormalized(normal) }
	,m_Color{ color }
	,m_Intensity{ intensity }
{
}

const RGBColor DirectionalLight::GetBiradianceBRDF(const FVector3& ray, const HitRecord& hitrecord) const
{
	if (!m_EnableDirectionalLight) return {};

	const RGBColor eRgb = m_Color * m_Intensity;
	switch (m_ToggleERGB)
	{
	case ToggleLight::BRDF:
		return RGBColor{ hitrecord.material->Shade(hitrecord, m_Direction, ray) };
		break;
	case ToggleLight::Irradiance:
		return RGBColor{ eRgb };
		break;
	case ToggleLight::IrradianceBRDF:
		return RGBColor{ eRgb * hitrecord.material->Shade(hitrecord, m_Direction, ray) };
		break;
	}
	return {};
}

const FVector3 DirectionalLight::GetDirection(const HitRecord& hitrecord) const
{
	return GetNormalized(m_Direction);
}

const FPoint3 DirectionalLight::GetPosition() const
{
	return FPoint3();
}

void DirectionalLight::SetState()
{
}
