#pragma once
#include "Material.h"
class Phong : public Material
{
public:
	Phong(const float diffuseReflectance, const float specularReflectance, const float phongExponent, const RGBColor& diffuseColor);
	~Phong() = default;
	virtual RGBColor Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const override;
private:
	const float m_SpecularReflectance;
	const float m_DiffuseReflectance;
	const float m_PhongExponent;
	const RGBColor m_DiffuseColor;
};

