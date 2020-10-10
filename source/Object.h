#pragma once
#include "struct.h"
#include "Material.h"

using namespace Elite;
class Object
{
public:
	Object(const Material* material);
	Object(const Object& rhs) = delete;
	Object(Object&& other) = delete;
	Object& operator=(const Object& rhs) = delete;
	Object& operator=(const Object&& other) = delete;
	~Object();

	virtual bool Hit(const Ray& ray, HitRecord& hitRecord) const = 0;
	virtual void Update(float elapsedSec) = 0;
protected:
	const Material* m_Material;
};
