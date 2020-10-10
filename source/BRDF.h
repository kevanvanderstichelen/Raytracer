#pragma once
#include "pch.h"
#include "SDL.h"

using namespace Elite;
class BRDF
{
public:
	BRDF() = default;
	~BRDF() = default;
	static const RGBColor Lambert(float diffuseReflectance, const RGBColor diffuseColor)
	{
		RGBColor test = (diffuseColor * diffuseReflectance);
		return { test / float(E_PI) };
	}
	static const RGBColor Lambert(const RGBColor diffuseReflectance, const RGBColor diffuseColor)
	{
		return (diffuseReflectance * diffuseColor) /= float(E_PI);
	}

	static const RGBColor Phong(float specReflFact, float phongExpon, const FVector3& l, const FVector3& v, const FVector3& n)
	{
		const FVector3 reflect = -l + (2.f * (Dot(n, l)) * n);
		const float cosAngle = Dot(reflect, v);
		const float phong = specReflFact * powf(cosAngle, phongExpon);
		return RGBColor{ phong,phong,phong };
	}

	static const RGBColor Fresnel(const FVector3& h, const FVector3& v, const RGBColor& f0)
	{
		return f0 + (RGBColor(1.f,1.f,1.f) - f0) * powf(1.f - (Dot(h, v)), 5.f);
	}

	static const float Distribution(const FVector3& n, const FVector3& h, float roughness)
	{
		const float a = roughness * roughness;
		const float a2 = a * a;
		const float NdotH = Dot(n, h);
		const float NdotH2 = NdotH * NdotH;

		const float f = NdotH2 * (a2 - 1.f) + 1.f;

		const float GGX_TR = a2 / (float(E_PI) * (f * f));

		return GGX_TR;
	}

	static const float Geometry(const FVector3& n, const FVector3& v, const FVector3& l, const float roughness)
	{
		const float a = roughness * roughness;
		const float k = ((a + 1.f) * (a + 1.f)) / 8.f;

		const float G_Smith = BRDF::G_SCHLICK(n, v, k) * BRDF::G_SCHLICK(n, l, k);

		return G_Smith;
	}

private:
	static const float G_SCHLICK(const FVector3& n, const FVector3& v, float k)
	{
		const float NdotV = Dot(n, v);
		const float schlick = NdotV / ( NdotV * ( 1.f - k ) + k );

		return schlick;
	}




};
