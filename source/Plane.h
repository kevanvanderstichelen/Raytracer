#pragma once
#include "Object.h"

using namespace Elite;

class Plane : public Object
{
public:
	Plane(const FPoint3& origin, const Material* material, const FVector3& normal);
	~Plane() = default;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) const override;
	virtual void Update(float elapsedSec) override;
private:
	const FPoint3 m_Origin;
	const FVector3 m_Normal;

};


