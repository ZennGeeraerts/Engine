// SmileEngineProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "SmileEnginePCH.h"
#include <SmileEngine.h>
#include "SceneManager.h"
#include "Scene.h"

#include "MainMenu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "CoopLevel1.h"
#include "CoopLevel2.h"
#include "CoopLevel3.h"
#include "VersusLevel1.h"
#include "VersusLevel2.h"
#include "VersusLevel3.h"

int main(int, char* []) 
{
	dae::SmileEngine engine{};
	engine.Initialize();

	auto gameSettings = engine.GetGameSettings();
	auto& sceneManager{ dae::SceneManager::GetInstance() };

	std::shared_ptr<dae::MainMenu> pMainMenu = std::make_shared<dae::MainMenu>(gameSettings);
	sceneManager.AddScene(pMainMenu);

	std::shared_ptr<dae::Level1> pLevel1 = std::make_shared<dae::Level1>(gameSettings);
	sceneManager.AddScene(pLevel1);

	std::shared_ptr<dae::Level2> pLevel2 = std::make_shared<dae::Level2>(gameSettings);
	sceneManager.AddScene(pLevel2);

	std::shared_ptr<dae::Level3> pLevel3 = std::make_shared<dae::Level3>(gameSettings);
	sceneManager.AddScene(pLevel3);

	std::shared_ptr<dae::CoopLevel1> pCoopLevel1 = std::make_shared<dae::CoopLevel1>(gameSettings);
	sceneManager.AddScene(pCoopLevel1);

	std::shared_ptr<dae::CoopLevel2> pCoopLevel2 = std::make_shared<dae::CoopLevel2>(gameSettings);
	sceneManager.AddScene(pCoopLevel2);

	std::shared_ptr<dae::CoopLevel3> pCoopLevel3 = std::make_shared<dae::CoopLevel3>(gameSettings);
	sceneManager.AddScene(pCoopLevel3);

	std::shared_ptr<dae::VersusLevel1> pVersusLevel1 = std::make_shared<dae::VersusLevel1>(gameSettings);
	sceneManager.AddScene(pVersusLevel1);

	std::shared_ptr<dae::VersusLevel2> pVersusLevel2 = std::make_shared<dae::VersusLevel2>(gameSettings);
	sceneManager.AddScene(pVersusLevel2);

	std::shared_ptr<dae::VersusLevel3> pVersusLevel3 = std::make_shared<dae::VersusLevel3>(gameSettings);
	sceneManager.AddScene(pVersusLevel3);

	sceneManager.SetScene(0);
	pMainMenu->CreateScene();

	engine.Run();
	return 0;
}