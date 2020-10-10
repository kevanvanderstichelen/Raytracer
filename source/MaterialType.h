#pragma once
#include "Struct.h"
#include "Material.h"
#include "PBR.h"
#include "Diffuse.h"
#include "Phong.h"

class MaterialType
{
public:
	struct M_PBR
	{
		static const Material* Gold(const float roughness = m_StandardRoughness, const float metalness = m_StandardMetalState)
		{ return new PBR(BaseColor::Gold(), roughness, metalness); };
		static const Material* Copper(const float roughness = m_StandardRoughness, const float metalness = m_StandardMetalState)
		{ return new PBR(BaseColor::Copper(), roughness, metalness); };
		static const Material* Silver(const float roughness = m_StandardRoughness, const float metalness = m_StandardMetalState)
		{ return new PBR(BaseColor::Silver(), roughness, metalness); };
		static const Material* Titanium(const float roughness = m_StandardRoughness, const float metalness = m_StandardMetalState)
		{ return new PBR(BaseColor::Titanium(), roughness, metalness); };
	};
	struct M_Diffuse
	{
		static const Material* LightBrown(const float reflectance = m_StandardDiffuseReflectance) { return new Diffuse(reflectance, BaseColor::LightBrown()); };
		static const Material* Silver(const float reflectance = m_StandardDiffuseReflectance) { return new Diffuse(reflectance, BaseColor::Silver()); };
	};
	struct M_Phong
	{
		static const Material* Silver(const float reflectanceD = m_StandardDiffuseReflectance
		, const float reflectanceS = m_StandardSpecularReflectance, const float phongExponent = m_StandardPhongExponent)
		{
			return new Phong(reflectanceD, reflectanceS, phongExponent, BaseColor::Silver());
		};
	
	};
private:
	static const float m_StandardMetalState;
	static const float m_StandardRoughness;
	static const float m_StandardDiffuseReflectance;
	static const float m_StandardSpecularReflectance;
	static const float m_StandardPhongExponent;
};

const float MaterialType::m_StandardMetalState{ 0.f };
const float MaterialType::m_StandardRoughness{ 0.5f };
const float MaterialType::m_StandardDiffuseReflectance{ 1.f };
const float MaterialType::m_StandardSpecularReflectance{ 0.5f };
const float MaterialType::m_StandardPhongExponent{ 60.f };
