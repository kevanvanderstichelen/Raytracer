#include "pch.h"
#include "Phong.h"

Phong::Phong(const float diffuseReflectance, const float specularReflectance, const float phongExponent, const RGBColor& diffuseColor)
	:m_DiffuseColor{ diffuseColor }
	,m_DiffuseReflectance { diffuseReflectance }
	,m_SpecularReflectance{ specularReflectance }
	,m_PhongExponent { phongExponent }
{
}

RGBColor Phong::Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const
{
	return BRDF::Lambert(m_DiffuseReflectance, m_DiffuseColor) 
		+ BRDF::Phong(m_SpecularReflectance, m_PhongExponent, l, v, hitRecord.normal);
}
