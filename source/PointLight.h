#pragma once
#include "Lights.h"

class PointLight : public Lights
{
public:
	PointLight(const FPoint3& pos, const RGBColor& color, float intensity);
	~PointLight() = default;
	virtual const RGBColor GetBiradianceBRDF(const FVector3& ray, const HitRecord& hitrecord) const override;
	virtual const FVector3 GetDirection(const HitRecord& hitrecord) const override;
	virtual const FPoint3 GetPosition() const override;
	virtual void SetState() override;
private:
	FPoint3 m_Position;
	RGBColor m_Color;
	float m_Intensity;
	bool m_CurrentState;

	
};

