#pragma once
#include "pch.h"
#include "Lights.h"
#include "LightManager.h"
#include "SDL.h"

bool Lights::m_EnableHardShadows{ true };
bool Lights::m_EnableDirectionalLight{ true };
int Lights::m_ToggleLightIndex{ 2 };
Lights::ToggleLight Lights::m_ToggleERGB{ Lights::ToggleLight::IrradianceBRDF };

const void Lights::HandleControls()
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_J])
	{
		m_EnableDirectionalLight = !m_EnableDirectionalLight;
	}
	if (pStates[SDL_SCANCODE_Z])
	{
		m_EnableHardShadows = !m_EnableHardShadows;
	}
	if (pStates[SDL_SCANCODE_K])
	{
		LightManager::GetInstance()->GetLightsFromGraph()[0]->SetState();
	}
	if (pStates[SDL_SCANCODE_L])
	{
		LightManager::GetInstance()->GetLightsFromGraph()[1]->SetState();
	}
	if (pStates[SDL_SCANCODE_T])
	{
		m_ToggleERGB = static_cast<ToggleLight>(++m_ToggleLightIndex %= 3);
	}
}

bool Lights::GetEnableHardShadow() const
{
	return m_EnableHardShadows;
}
