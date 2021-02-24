#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "C_Text.h"
#include "GameObject.h"
#include "Scene.h"
#include "Time.h"
#include "C_Renderer.h"
#include "C_Transform.h"
#include "C_FPSCounter.h"

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	auto renderer = go->AddComponent<C_Renderer>();
	renderer->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	renderer = go->AddComponent<C_Renderer>();
	renderer->SetTexture("logo.png");
	go->GetComponent<C_Transform>()->SetPosition(216, 180, 0);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent<C_Renderer>();
	auto to = go->AddComponent<C_Text>();
	to->SetText("Programming 4 assignment");
	to->SetFont(font);
	go->GetComponent<C_Transform>()->SetPosition(80, 20, 0);
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent<C_Renderer>();
	to = go->AddComponent<C_Text>();
	to->SetText("FPS");
	to->SetFont(font);
	go->AddComponent<C_FPSCounter>();
	go->GetComponent<C_Transform>()->SetPosition(10, 10, 0);
	scene.Add(go);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time{ Time::GetInstance() };

		time.Run();
		bool doContinue = true;
		while (doContinue)
		{
			time.Update();
			doContinue = input.ProcessInput();

			while (time.IsCatchingUpInFixedSteps())
			{
				sceneManager.FixedUpdate();
			}
			sceneManager.Update();
			sceneManager.LateUpdate();

			renderer.Render();
		}
	}

	Cleanup();
}
