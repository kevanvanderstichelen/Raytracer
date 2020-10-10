#pragma once

#include "Object.h"
#include "PointLight.h"
#include <vector>

using namespace Elite;
class SceneGraph
{
public:
	static SceneGraph* GetInstance();
	static void AddObjectToGraph(Object* object);
	static const std::vector<Object*>& GetObjectsFromGraph();
	static void ResetInstance();

private:
	static SceneGraph* m_Instance;
	static std::vector<Object*> m_Objects;
	SceneGraph() = default;
	~SceneGraph();
};
