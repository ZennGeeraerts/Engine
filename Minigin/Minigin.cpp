#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "GameObject.h"
#include "Scene.h"
#include "Time.h"

#include "C_Text.h"
#include "C_Render.h"
#include "C_Transform.h"
#include "C_FPSCounter.h"
#include "C_Health.h"

#include "InputCommands.h"
#include "InputManager.h"

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

	auto pGameObject = std::make_shared<GameObject>();
	auto pRenderer = pGameObject->AddComponent<C_Render>();
	pRenderer->SetTexture("background.jpg");
	scene.Add(pGameObject);

	pGameObject = std::make_shared<GameObject>();
	pRenderer = pGameObject->AddComponent<C_Render>();
	pRenderer->SetTexture("logo.png");
	pGameObject->GetComponent<C_Transform>()->SetPosition(216, 180, 0);
	scene.Add(pGameObject);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	pGameObject = std::make_shared<GameObject>();
	pGameObject->AddComponent<C_Render>();
	auto pText = pGameObject->AddComponent<C_Text>();
	pText->SetText("Programming 4 assignment");
	pText->SetFont(font);
	pGameObject->GetComponent<C_Transform>()->SetPosition(80, 20, 0);
	scene.Add(pGameObject);

	pGameObject = std::make_shared<GameObject>();
	pGameObject->AddComponent<C_Render>();
	pText = pGameObject->AddComponent<C_Text>();
	pText->SetText("FPS");
	pText->SetFont(font);
	pGameObject->AddComponent<C_FPSCounter>();
	pGameObject->GetComponent<C_Transform>()->SetPosition(10, 10, 0);
	scene.Add(pGameObject);

	// Create QBert GameObject
	auto& inputManager{ InputManager::GetInstance() };
	auto pQBert = new GameObject{ "Q*Bert" };
	auto pHealth = pQBert->AddComponent<C_Health>();
	pHealth->SetHealth(1);
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonA, new PlayerDie{ pQBert, InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonY, new Quit{ InputManager::InputKeyAction::ePressed });
	scene.Add(std::shared_ptr<GameObject>{ pQBert });
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
			const auto currentTime = high_resolution_clock::now();
			time.Update();
			doContinue = input.ProcessInput();

			while (time.IsCatchingUpInFixedSteps())
			{
				sceneManager.FixedUpdate();
			}
			sceneManager.Update();
			sceneManager.LateUpdate();

			renderer.Render();

			auto sleepTime = duration_cast<duration<float>>(time.GetTimeBeforeGameLoop() + milliseconds(time.GetMsPerFrame()) - high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
