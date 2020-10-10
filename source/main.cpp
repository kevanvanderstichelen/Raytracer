#include "pch.h"
//External includes
#include "vld.h"
#include "SDL.h"
#include "SDL_surface.h"
#undef main

//Standard includes
#include <iostream>

//Project includes
#include "ETimer.h"
#include "ERenderer.h"
#include "SceneGraph.h"
#include "SceneCamera.h"
#include "Plane.h"
#include "Sphere.h"
#include "Material.h"
#include "Diffuse.h"
#include "Triangle.h"
#include "MaterialType.h"
#include "TriangleMesh.h"

void ShutDown(SDL_Window* pWindow)
{
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}

int main(int argc, char* args[])
{
	//Unreferenced parameters
	(void)argc;
	(void)args;

	//Create window + surfaces
	SDL_Init(SDL_INIT_VIDEO);

	const uint32_t width = 1920;
	const uint32_t height = 1080;
	SDL_Window* pWindow = SDL_CreateWindow(
		"RayTracer - Kevan Vanderstichelen",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width, height, 0);

	if (!pWindow)
		return 1;

	//Initialize "framework"
	Elite::Timer* pTimer = new Elite::Timer(); 
	Elite::Renderer* pRenderer = new Elite::Renderer(pWindow);
	SceneCamera* pCamera = new SceneCamera(FVector3{0,2.0f,11},45.f,float(width), float(height));

	//LIGHTS
	LightManager::GetInstance()->AddLightToGraph(new PointLight(FPoint3{ 0.f, 5.f, -5.f }, RGBColor{ 255.f / 255.f, 239.f / 255.f, 201.f / 255.f }, 35.f));
	LightManager::GetInstance()->AddLightToGraph(new PointLight(FPoint3{ 0.f, 5.f, 5.f }, RGBColor{ 255.f / 255.f, 239.f / 255.f, 201.f / 255.f }, 50.f));
	LightManager::GetInstance()->AddLightToGraph(new DirectionalLight(FVector3{ 0.f, 1.f, 1.f }, RGBColor{ 242.f / 255.f, 247.f / 255.f, 255.f / 255.f }, 0.5f));
	//ROOM
	SceneGraph::GetInstance()->AddObjectToGraph(new Plane(FPoint3{ 0.f, -0.f, 0.f }, MaterialType::M_Diffuse::LightBrown(), FVector3{ 0.f, 1.f, 0.f }));
	SceneGraph::GetInstance()->AddObjectToGraph(new Plane(FPoint3{ 0.f, 0.f, -10.f }, MaterialType::M_Diffuse::LightBrown(), FVector3{ 0.f, 0.f, 1.f }));
	SceneGraph::GetInstance()->AddObjectToGraph(new Plane(FPoint3{ -7.f, 0.f, 0.f }, MaterialType::M_Diffuse::LightBrown(), FVector3{ 1.f, 0.f, 0.f }));
	SceneGraph::GetInstance()->AddObjectToGraph(new Plane(FPoint3{ 7.f, 0.f, 0.f }, MaterialType::M_Diffuse::LightBrown(), FVector3{ -1.f, 0.f, 0.f }));
	
	//----------------------------------------------SCENE ONE-----------------------------------------
	//LOWER SPHERES
	//SceneGraph::GetInstance()->AddObjectToGraph(new Sphere(FPoint3{ 2.5f, 1.5f, 0.f }, MaterialType::M_PBR::Copper(0.1f, 0.f) , 1.f));
	//SceneGraph::GetInstance()->AddObjectToGraph(new Sphere(FPoint3{ 0.f, 1.5f, 0.f }, MaterialType::M_PBR::Silver(0.15f, 0.f), 1.f));
	//SceneGraph::GetInstance()->AddObjectToGraph(new Sphere(FPoint3{ -2.5f, 1.5f, 0.f }, MaterialType::M_PBR::Titanium(0.7f, 0.0f), 1.f));
	////UPPER SPHERES
	//SceneGraph::GetInstance()->AddObjectToGraph(new Sphere(FPoint3{ 2.5f, 4.f, 0.f }, MaterialType::M_PBR::Copper(1.f, 0.f), 1.f));
	//SceneGraph::GetInstance()->AddObjectToGraph(new Sphere(FPoint3{ 0.f, 4.f, 0.f }, MaterialType::M_PBR::Silver(0.8f, 1.f), 1.f));
	//SceneGraph::GetInstance()->AddObjectToGraph(new Sphere(FPoint3{ -2.5f, 4.f, 0.f }, MaterialType::M_PBR::Gold(0.7f, 1.f), 1.f));
	////TRIANGLES
	//SceneGraph::GetInstance()->AddObjectToGraph(new Triangle(FPoint3(0,6,0),FVector3(-.75f, 1.5f, 0.f), FVector3(-.75f, 0.f, 0.f), FVector3(.75f, 0.f, 0.f), MaterialType::M_Diffuse::Silver(), Culling::None));
	//SceneGraph::GetInstance()->AddObjectToGraph(new Triangle(FPoint3(2.5f, 6, 0), FVector3(-.75f, 1.5f, 0.f), FVector3(-.75f, 0.f, 0.f), FVector3(.75f, 0.f, 0.f), MaterialType::M_Diffuse::Silver(), Culling::Front));
	//SceneGraph::GetInstance()->AddObjectToGraph(new Triangle(FPoint3(-2.5f, 6, 0), FVector3(-.75f, 1.5f, 0.f), FVector3(-.75f, 0.f, 0.f), FVector3(.75f, 0.f, 0.f), MaterialType::M_Diffuse::Silver(), Culling::Back));

	//----------------------------------------------SCENE TWO-----------------------------------------
	//SceneGraph::GetInstance()->AddObjectToGraph(TriangleMesh::LoadFromFile("test.obj", FVector3(0, 0, 0), MaterialType::M_PBR::Silver(0.1f, 0.f))); // TEST
	SceneGraph::GetInstance()->AddObjectToGraph(TriangleMesh::LoadFromFile("lowpoly_bunny.obj", FVector3(0, 0, 0), MaterialType::M_PBR::Silver(0.05f, 0.f)));

	//Start loop
	pTimer->Start();
	float printTimer = 0.f;
	bool isLooping = true;
	bool takeScreenshot = false;
	while (isLooping)
	{
		//--------- Get input events ---------
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				isLooping = false;
				break;
			case SDL_KEYUP:
				if(e.key.keysym.scancode == SDL_SCANCODE_X)
					takeScreenshot = true;
				break;
			}
		}

		//--------- key input ---------
		pCamera->HandleMouse(pTimer->GetElapsed());
		LightManager::GetInstance()->GetLightsFromGraph()[0]->HandleControls();

		//--------- Update -------------
		for (Object* obj : SceneGraph::GetObjectsFromGraph()) obj->Update(pTimer->GetElapsed());

		//--------- Render ---------
		pRenderer->Render(pCamera);

		//--------- Timer ---------
		pTimer->Update();
		printTimer += pTimer->GetElapsed();
		if (printTimer >= 1.f)
		{
			printTimer = 0.f;
			std::cout << "FPS: 10" << pTimer->GetFPS() << std::endl;
		}

		//Save screenshot after full render
		if (takeScreenshot)
		{
			if (!pRenderer->SaveBackbufferToImage())
				std::cout << "Screenshot saved!" << std::endl;
			else
				std::cout << "Something went wrong. Screenshot not saved!" << std::endl;
			takeScreenshot = false;
		}
	}
	pTimer->Stop();
	

	//Shutdown "framework"
	SceneGraph::ResetInstance();
	LightManager::ResetInstance();
	delete pRenderer;
	delete pTimer;
	delete pCamera;

	ShutDown(pWindow);
	return 0;
}