#pragma once
#include "Object.h"
#include "Struct.h"
class Triangle : public Object
{
public:
	Triangle(const FPoint3& pos, const FVector3& v0, const FVector3& v1, const FVector3& v2, const Material* material, const Culling& culling);
	~Triangle() = default;
	virtual bool Hit(const Ray& ray, HitRecord& hitrecord) const override;
	virtual void Update(float elapsedSec) override;
private:
	const float m_RotationRatio;

	FVector3 m_V0;
	FVector3 m_V1;
	FVector3 m_V2;

	Culling m_Culling;

	FVector3 m_Position;
	FVector3 m_Center;
	FVector3 m_Normal;

	FMatrix4 m_Matrix;

};

