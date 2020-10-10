#pragma once
#include "Struct.h"

class Lights
{
public:
	Lights() = default;
	~Lights() = default;
	virtual const RGBColor GetBiradianceBRDF(const FVector3& ray, const HitRecord& hitrecord) const = 0;
	virtual const FVector3 GetDirection(const HitRecord& hitrecord) const = 0;
	virtual const FPoint3 GetPosition() const = 0;
	const void HandleControls();
	bool GetEnableHardShadow() const;
	virtual void SetState() = 0;

private:
	static bool m_EnableHardShadows;
	static int m_ToggleLightIndex;

protected:
	static bool m_EnableDirectionalLight;
	enum class ToggleLight
	{
		BRDF = 0,
		Irradiance = 1,
		IrradianceBRDF = 2
	};
	static ToggleLight m_ToggleERGB;

};

