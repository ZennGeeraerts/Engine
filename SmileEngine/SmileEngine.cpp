#include "SmileEnginePCH.h"
#include "SmileEngine.h"
#include <thread>
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>

#include "GameObject.h"
#include "Scene.h"
#include "SmTime.h"

// Components
#include "C_Text.h"
#include "C_Render.h"
#include "C_Transform.h"
#include "C_FPSCounter.h"

// UI
#include "UIManager.h"
#include "GameModeMenu.h"
#include "ControlsMenu.h"

// Prefabs
#include "Player.h"

// Input
#include "InputManager.h"
#include "InputCommands.h"

// Sound
#include "ServiceLocator.h"
#include "SDLSoundSystem.h"

// Lua
#include "LuaVM.h"
#include "LuaFunctions.h"

using namespace std;
using namespace std::chrono;

void dae::SmileEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_pWindow);

	m_pSoundSystem = new SDLSoundSystem{};

	m_pLuaVM = new LuaVM{};
	m_pLuaVM->ExecuteString("a = 1 + 1", "a");
	m_pLuaVM->RegisterFunction("addNPC", dae::addNPC);
	m_pLuaVM->RegisterFunction("removeNPC", dae::removeNPC);
	m_pLuaVM->RegisterFunction("dump", dae::dump);
	m_pLuaVM->RegisterFunction("setHealth", dae::setHealth);
	m_pLuaVM->ExecuteFile("../Data/NPC.lua");
}

/**
 * Code constructing the scene world starts here
 */
void dae::SmileEngine::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	auto& uiManager = UIManager::GetInstance();
	auto& inputManager = InputManager::GetInstance();

	ServiceLocator::RegisterSoundSystem(m_pSoundSystem);

	// Input
	inputManager.AddInputAction(SDL_SCANCODE_A, new Quit{ InputManager::InputKeyAction::eDown });

	// UI
	uiManager.AddUILayer(new GameModeMenu{ glm::vec2{ 200.f, 0.0f }, m_pWindow });
	uiManager.AddUILayer(new ControlsMenu{ glm::vec2{ 200.f, 150.f }, m_pWindow });

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

	std::shared_ptr<Player> pPlayer = std::make_shared<Player>(Player{ glm::vec2{ 0.0f, 0.0f }, m_pWindow, XBoxController::ControllerButton::eButtonA, XBoxController::ControllerButton::eButtonB });
	scene.Add(std::shared_ptr<GameObject>{ pPlayer->CreatePrefab() });

	pPlayer = std::make_shared<Player>(Player{ glm::vec2{ 0.0f, 150.0f }, m_pWindow, XBoxController::ControllerButton::eButtonDown, XBoxController::ControllerButton::eButtonRight });
	scene.Add(std::shared_ptr<GameObject>{ pPlayer->CreatePrefab() });
}

void dae::SmileEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_Quit();

	delete m_pSoundSystem;
	delete m_pLuaVM;
}

void dae::SmileEngine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& time{ SmTime::GetInstance() };

		time.Run();
		bool doContinue = time.GetDoContinue();
		while (doContinue)
		{
			time.Update();
			doContinue = input.ProcessInput();
			time.SetDoContinue(doContinue);

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