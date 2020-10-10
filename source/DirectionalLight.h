#pragma once
#include "LightManager.h"
class DirectionalLight : public Lights
{
public:
	DirectionalLight(const FVector3& normal, const RGBColor& color, float intensity);
	~DirectionalLight() = default;
	virtual const RGBColor GetBiradianceBRDF(const FVector3& ray, const HitRecord& hitrecord) const override;
	virtual const FVector3 GetDirection(const HitRecord& hitrecord) const override;
	virtual const FPoint3 GetPosition() const override;
	virtual void SetState() override;
private:
	const FVector3 m_Direction;
	const RGBColor m_Color;
	const float m_Intensity;

};

