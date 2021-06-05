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

	sceneManager.SetScene(0);
	pMainMenu->CreateScene();

	engine.Run();
	return 0;
}