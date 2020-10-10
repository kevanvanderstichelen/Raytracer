#include "pch.h"
#include "Diffuse.h"

Diffuse::Diffuse(const float diffuseReflectance, const RGBColor& diffuseColor)
	:m_DiffuseReflectance{ diffuseReflectance }
	,m_DiffuseColor { diffuseColor }
{
}

RGBColor Diffuse::Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColor);
}
