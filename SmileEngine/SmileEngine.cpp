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

	m_GameSettings.m_WindowWidth = 640;
	m_GameSettings.m_WindowHeight = 480;

	m_GameSettings.m_pWindow = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_GameSettings.m_WindowWidth,
		m_GameSettings.m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_GameSettings.m_pWindow == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_GameSettings.m_pWindow);

	m_pSoundSystem = new SDLSoundSystem{};

	m_pLuaVM = new LuaVM{};
	m_pLuaVM->ExecuteString("a = 1 + 1", "a");
	m_pLuaVM->RegisterFunction("addNPC", dae::addNPC);
	m_pLuaVM->RegisterFunction("removeNPC", dae::removeNPC);
	m_pLuaVM->RegisterFunction("dump", dae::dump);
	m_pLuaVM->RegisterFunction("setHealth", dae::setHealth);
	m_pLuaVM->ExecuteFile("../Data/NPC.lua");

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();
}

/**
 * Code constructing the scene world starts here
 */
void dae::SmileEngine::LoadGame() const
{
	//auto& uiManager = UIManager::GetInstance();
	auto& inputManager = InputManager::GetInstance();

	ServiceLocator::RegisterSoundSystem(m_pSoundSystem);

	// Input
	inputManager.AddInputAction(SDL_SCANCODE_ESCAPE, new Quit{ InputManager::InputKeyAction::eDown });
}

const dae::GameSettings& dae::SmileEngine::GetGameSettings() const
{
	return m_GameSettings;
}

void dae::SmileEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_GameSettings.m_pWindow);
	m_GameSettings.m_pWindow = nullptr;
	SDL_Quit();

	delete m_pSoundSystem;
	delete m_pLuaVM;
}

void dae::SmileEngine::Run()
{
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