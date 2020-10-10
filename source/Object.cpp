#include "pch.h"
#include "Object.h"

Object::Object(const Material* material)
	:m_Material{ material }
{
}

Object::~Object()
{
	delete m_Material;
	m_Material = nullptr;
}
