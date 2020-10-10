#pragma once
#include "Material.h"
class Diffuse : public Material
{
public:
	Diffuse(const float diffuseReflectance, const RGBColor& diffuseColor);
	~Diffuse() = default;
	virtual RGBColor Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const override;
private:
	const float m_DiffuseReflectance;
	const RGBColor m_DiffuseColor;
};

