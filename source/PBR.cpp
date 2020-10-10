#include "pch.h"
#include "PBR.h"

PBR::PBR(const RGBColor& albedo, const float roughness, const float metalness)
	:m_Albedo { albedo }
	,m_Roughness { roughness }
	,m_Metalness{ metalness == 0.f ? RGBColor{ 0.04f, 0.04f, 0.04f } : albedo }
	,m_Metal { metalness == 0.f ? false : true }
{

}

RGBColor PBR::Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const
{
	const FVector3 n = hitRecord.normal;
	const FVector3 h = GetNormalized(l + v);

	const RGBColor F = BRDF::Fresnel(h, v, m_Metalness);
	const float D = BRDF::Distribution(n, h, m_Roughness);
	const float G = BRDF::Geometry(n, v, l, m_Roughness);

	const RGBColor cookTorrance = ( F * G * D ) / ( 4 * Dot(v, n) * Dot(l, n) );

	const RGBColor kd = m_Metal ? RGBColor{ 0.f, 0.f, 0.f } : RGBColor{ 1,1,1 } - F;
	const RGBColor ks = F;

	const RGBColor diffuse = BRDF::Lambert(kd, m_Albedo);

	return ( kd * diffuse ) + ( ks * cookTorrance );

}
