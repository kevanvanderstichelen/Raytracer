#pragma once
#include "pch.h"
#include "EVector3.h"
#include "EPoint3.h"
#include "Math.h"
class Material;
using namespace Elite;

struct Ray
{
	FPoint3 origin;
	FVector3 direction;
	float tMin = 0.0001f;
	float tMax = FLT_MAX;
};

struct HitRecord
{
	float tValue{FLT_MAX};
	const Material* material{};
	FPoint3 hitPoint;
	FVector3 normal;
};

struct BaseColor
{
	static const RGBColor White() { return RGBColor{ 1.f, 1.f, 1.f }; };
	static const RGBColor Grey() { return RGBColor{ 0.55f, 0.5f, 0.5f }; };
	static const RGBColor Black() { return RGBColor{ 0.f, 0.f, 0.f }; };
	static const RGBColor Copper() { return RGBColor{ 0.955f, 0.638f, 0.538f }; };
	static const RGBColor Silver() { return RGBColor{ 0.972f, 0.960f, 0.915f }; };
	static const RGBColor Gold() { return RGBColor{ 1.f, 0.782f, 0.344f }; };
	static const RGBColor LightBrown() { return RGBColor{ 181.f / 255.f, 161.f / 255.f, 143.f / 255.f }; };
	static const RGBColor Titanium() { return RGBColor{ 0.542f, 0.497f, 0.499f }; };
};

enum Culling { None, Front, Back };

struct Triplet
{
	unsigned int one, two, three;
};
