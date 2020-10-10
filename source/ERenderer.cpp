#include "pch.h"
//External includes
#include "SDL.h"
#include "SDL_surface.h"
#include "struct.h"

//Project includes
#include "ERenderer.h"

Elite::Renderer::Renderer(SDL_Window* pWindow)
	:m_pWindow{ pWindow }
	, m_pFrontBuffer{ SDL_GetWindowSurface(pWindow) }
	, m_pBackBuffer{}
	, m_pBackBufferPixels{}
	, m_Width{}
	, m_Height{}
{
	//Initialize
	int width, height = 0;
	SDL_GetWindowSize(pWindow, &width, &height);
	m_Width = static_cast<uint32_t>(width);
	m_Height = static_cast<uint32_t>(height);
	m_pBackBuffer = SDL_CreateRGBSurface(0, m_Width, m_Height, 32, 0, 0, 0, 0);
	m_pBackBufferPixels = (uint32_t*)m_pBackBuffer->pixels;
}

void Elite::Renderer::Render(SceneCamera* pCamera)
{
	SDL_LockSurface(m_pBackBuffer);

	//Loop over all the pixels
	for (uint32_t r = 0; r < m_Height; ++r)
	{
		for (uint32_t c = 0; c < m_Width; ++c)
		{
			Ray ray;
			HitRecord hitRecord;
			RGBColor finalColor{ 0.f, 0.f, 0.f };
			pCamera->SetRay(ray, c, r);

			if (TraceRay(ray, hitRecord)) finalColor = CalculatePixelsColor(ray, hitRecord);

			m_pBackBufferPixels[c + (r * m_Width)] = SDL_MapRGB(m_pBackBuffer->format,
				static_cast<uint8_t>(255.f * finalColor.r),
				static_cast<uint8_t>(255.f * finalColor.g),
				static_cast<uint8_t>(255.f * finalColor.b));
		}
	}

	SDL_UnlockSurface(m_pBackBuffer);
	SDL_BlitSurface(m_pBackBuffer, 0, m_pFrontBuffer, 0);
	SDL_UpdateWindowSurface(m_pWindow);
}

bool Elite::Renderer::SaveBackbufferToImage() const
{
	return SDL_SaveBMP(m_pBackBuffer, "BackbufferRender.bmp");
}

bool Elite::Renderer::TraceRay(const Ray& ray, HitRecord& hitrecord) const
{
	HitRecord objectHit;
	bool isHit = false;
	for (const Object* obj : SceneGraph::GetObjectsFromGraph())
	{
		if (obj->Hit(ray, objectHit) && objectHit.tValue < hitrecord.tValue)
		{
			hitrecord = objectHit;
			isHit = true;
		}
	}
	return isHit ? true : false;
}


const RGBColor Elite::Renderer::CalculatePixelsColor(Ray& ray, const HitRecord& hitRecord) const
{
	const FVector3 rayPrevVal = GetNormalized(-ray.direction);
	RGBColor finalColor;
	for (const Lights* light : LightManager::GetLightsFromGraph())
	{
		const FVector3 lightDirection = { light->GetDirection(hitRecord) };
		ray = { hitRecord.hitPoint, lightDirection, 0.0001f, Distance(hitRecord.hitPoint, light->GetPosition()) };
		HitRecord shadowHitRecord;
		if (light->GetEnableHardShadow() && TraceRay(ray, shadowHitRecord)) continue;

		const float observedArea = Dot(hitRecord.normal, lightDirection);
		if (observedArea < 0.f) continue;

		finalColor += light->GetBiradianceBRDF(rayPrevVal, hitRecord) * observedArea;
	}

	finalColor.MaxToOne();
	return finalColor;
}
