#pragma once
#include "pch.h"
#include "SDL.h"
#include "BRDF.h"
#include "struct.h"

using namespace Elite;

class Material
{
public:
	Material() = default;
	~Material() = default;
	virtual RGBColor Shade(const HitRecord& hitRecord, const FVector3& l, const FVector3& v) const = 0;
};

