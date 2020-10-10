#pragma once
#include "EMath.h"
#include "SDL.h"
#include "struct.h"
using namespace Elite;
class SceneCamera
{
public:
	SceneCamera(const FVector3& position, const float FOV, const float sWidth, const float sHeight);
	~SceneCamera() = default;
	void HandleMouse(const float elapsedSec);
	void SetRay(Ray& ray, const uint32_t& c, const uint32_t& r) const;
private:
	//Mouse settings
	bool m_LeftMouseButton;
	bool m_RightMouseButton;
	
	//Camera settings
	float m_FOV;
	const float m_ScreenWidth;
	const float m_ScreenHeight;
	const float m_AspectRatio;
	const float m_MouseSensivity;
	const float m_TranslateRate;

	FVector2 m_CameraSpace;
	FMatrix4 m_Matrix;

	const FVector2 ConvertToScreenSpace(const uint32_t& c, const uint32_t& r) const;


};

