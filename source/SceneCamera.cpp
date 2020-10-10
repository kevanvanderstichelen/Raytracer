#include "pch.h"
#include "SceneCamera.h"
#include <iostream>

SceneCamera::SceneCamera(const FVector3& position, float FOV, float sWidth, float sHeight)
	:m_ScreenWidth{ float(sWidth) }
	,m_ScreenHeight{ float(sHeight) }
	,m_AspectRatio{ float(sWidth) / float(sHeight) }
	,m_FOV{ tanf(ToRadians(FOV) / 2)}
	,m_LeftMouseButton{}
	,m_RightMouseButton{}
	,m_Matrix{}
	,m_MouseSensivity{1.f}
	,m_TranslateRate{ 1.f }
{
	const FVector3 worldUp = { 0.f, 1.f, 0.f };
	const FVector3 forward = { 0.f, 0.f, -1.f };
	const FVector3 right = GetNormalized(Cross(worldUp, forward));
	const FVector3 up = Cross(forward, right);
	m_Matrix = { FVector4{right, 0.f}, FVector4{up, 0.f}, FVector4{forward, 0.f}, FVector4{position, 1.f} };
}

const FVector2 SceneCamera::ConvertToScreenSpace(const uint32_t& c, const uint32_t& r) const
{
	return FVector2{ (2 * ((c + 0.5f) / m_ScreenWidth) - 1) * m_AspectRatio * m_FOV, (1 - 2 * ((r + 0.5f) / m_ScreenHeight)) * m_FOV };
}

void SceneCamera::HandleMouse(const float elapsedSec)
{
	int mouseX{};
	int mouseY{};
	uint32_t mouseState = SDL_GetRelativeMouseState(&mouseX, &mouseY);

	if (mouseState & SDL_BUTTON(1) && mouseState & SDL_BUTTON(3))
	{
		m_Matrix *= MakeTranslation(FVector3(0, float(mouseY) * elapsedSec * m_TranslateRate, 0));
	}
	else if (mouseState & SDL_BUTTON(1))
	{
		m_Matrix *= MakeTranslation(FVector3(0, 0, float(mouseY) * elapsedSec * m_TranslateRate));
		m_Matrix *= FMatrix4(MakeRotationY(float(mouseX) * elapsedSec * m_MouseSensivity));
	}
	else if (mouseState & SDL_BUTTON(3))
	{
		m_Matrix *= FMatrix4(MakeRotationX(float(mouseY) * elapsedSec * m_MouseSensivity));
		m_Matrix *= FMatrix4(MakeRotationY(float(mouseX) * elapsedSec * m_MouseSensivity));
	}
}

void SceneCamera::SetRay(Ray& ray, const uint32_t& c, const uint32_t& r) const
{
	FVector4 direction = { ConvertToScreenSpace(c,r), 1.f, 0.f };
	direction = m_Matrix * direction;
	ray.direction = direction.xyz;
	ray.origin = FPoint3(m_Matrix[3].xyz);
}