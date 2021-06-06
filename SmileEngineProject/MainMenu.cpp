#include "SmileEnginePCH.h"
#include "MainMenu.h"
#include "GameModeMenu.h"
#include "UIManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"

// Components
#include "C_Render.h"
#include "C_Transform.h"
#include "C_Text.h"

dae::MainMenu::MainMenu(const GameSettings& gameSettings)
	: Scene(gameSettings)
{

}

void dae::MainMenu::CreateScene()
{
	auto pGameObject = std::make_shared<GameObject>();
	auto pRenderer = pGameObject->AddComponent<C_Render>();
	pRenderer->SetTexture("background.jpg");
	Add(pGameObject);

	pGameObject = std::make_shared<GameObject>();
	pRenderer = pGameObject->AddComponent<C_Render>();
	pRenderer->SetTexture("logo.png");
	pGameObject->GetComponent<C_Transform>()->SetPosition(216, 180, 0);
	Add(pGameObject);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	pGameObject = std::make_shared<GameObject>();
	pGameObject->AddComponent<C_Render>();
	auto pText = pGameObject->AddComponent<C_Text>();
	pText->SetText("Programming 4 assignment");
	pText->SetFont(font);
	pGameObject->GetComponent<C_Transform>()->SetPosition(80, 20, 0);
	Add(pGameObject);

	auto& uiManager = UIManager::GetInstance();
	uiManager.AddUILayer(new GameModeMenu{ glm::vec2{ 200.f, 0.0f } });
}