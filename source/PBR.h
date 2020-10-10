#pragma once
#include "Material.h"

class PBR : public Material
{
public:
	PBR(const RGBColor& albedo, const float roughness, const float metalness);
	~PBR() = default;
	virtual RGBColor Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const override;

private:
	const bool m_Metal;
	const RGBColor m_Metalness;
	const float m_Roughness;
	const RGBColor m_Albedo;
};

