#pragma once
#include "Object.h"

using namespace Elite;
class Sphere : public Object
{
public:
	Sphere(const FPoint3& origin, const Material* material, const float radius);
	~Sphere() = default;
	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) const override;
	virtual void Update(float elapsedSec) override;
private:
	const float m_Radius;
	const FPoint3 m_Origin;

};

