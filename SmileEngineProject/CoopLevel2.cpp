#include "SmileEnginePCH.h"
#include "CoopLevel2.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Input.h"
#include "UIManager.h"
#include "PlayerUI.h"
#include "LevelParser.h"

// Components
#include "C_Render.h"
#include "C_Transform.h"
#include "C_Text.h"
#include "C_FPSCounter.h"
#include "C_GameManager.h"
#include "C_QBertMovement.h"
#include "C_Health.h"
#include "C_Lives.h"
#include "C_CoilyController.h"
#include "C_Tile.h"
#include "C_UggController.h"
#include "C_WrongwayController.h"
#include "C_SlickAndSlamController.h"
#include "C_Teleport.h"
#include "C_Score.h"
#include "C_PlayerCollision.h"

dae::CoopLevel2::CoopLevel2(const GameSettings& gameSettings)
	: Scene(gameSettings)
{

}

void dae::CoopLevel2::CreateScene()
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

	pGameObject = std::make_shared<GameObject>();
	pGameObject->AddComponent<C_Render>();
	pText = pGameObject->AddComponent<C_Text>();
	pText->SetText("FPS");
	pText->SetFont(font);
	pGameObject->AddComponent<C_FPSCounter>();
	pGameObject->GetComponent<C_Transform>()->SetPosition(10, 10, 0);
	Add(pGameObject);

	// Tilemap
	auto pTileMapObj = std::make_shared<GameObject>();
	const int nrOfRows{ 7 };
	const float tileSize{ 32.f };

	std::vector<glm::vec3> tilePositions{};
	LevelParser levelParser{};

#if defined(WIN32)
	CreateTilePositions(tilePositions, tileSize, nrOfRows);
#endif

	if (!levelParser.ReadLevelBin("../Data/levelBin.bin", tilePositions))
	{
		CreateTilePositions(tilePositions, tileSize, nrOfRows);
		levelParser.WriteLevelBin("../Data/levelBin.bin", tilePositions);
	}
	for (const auto& tilePos : tilePositions)
	{
		auto pTileObj = new GameObject();
		C_Transform* pTransform = pTileObj->GetComponent<C_Transform>();
		pTransform->SetPosition(tilePos.x, tilePos.y, tilePos.z);
		pTileObj->AddComponent<C_Render>();
		auto pTile = pTileObj->AddComponent<C_Tile>();
		pTile->SetMaxStage(2);
		pTileMapObj->AddChild(pTileObj);
	}

	pTileMapObj->SetName("TileMap0");
	Add(pTileMapObj);

	// Teleport
	auto pTeleportObj = std::make_shared<GameObject>();
	pTeleportObj->SetTag("Teleport");
	Add(pTeleportObj);
	auto pRenderTp = pTeleportObj->AddComponent<C_Render>();
	pRenderTp->SetTexture("tp_0.png");
	auto pTeleport = pTeleportObj->AddComponent<C_Teleport>();
	pTeleport->SetConnectedTile(10, C_QBertMovement::MovementDirection::eTopLeft);
	pTeleport->SetTexturePaths(std::vector<std::string>{ "tp_0.png", "tp_1.png", "tp_2.png", "tp_3.png" });

	auto pTeleportObj2 = std::make_shared<GameObject>();
	pTeleportObj2->SetTag("Teleport");
	Add(pTeleportObj2);
	auto pRenderTp2 = pTeleportObj2->AddComponent<C_Render>();
	pRenderTp2->SetTexture("tp_0.png");
	auto pTeleport2 = pTeleportObj2->AddComponent<C_Teleport>();
	pTeleport2->SetConnectedTile(14, C_QBertMovement::MovementDirection::eTopRight);
	pTeleport2->SetTexturePaths(std::vector<std::string>{ "tp_0.png", "tp_1.png", "tp_2.png", "tp_3.png" });

	// Player1
	auto pPlayer = std::make_shared<GameObject>("Player 1");
	pPlayer->SetTag("Friendly");
	Add(pPlayer);
	auto& inputManager{ InputManager::GetInstance() };

	auto pLives = pPlayer->AddComponent<C_Lives>();
	pLives->SetLives(3);

	auto pHealth = pPlayer->AddComponent<C_Health>();
	pHealth->SetHealth(1);

	auto pScore = pPlayer->AddComponent<C_Score>();

	auto pRenderPlayer = pPlayer->AddComponent<C_Render>();
	pRenderPlayer->SetTexture("qbert_0.png");

	auto pMovementPlayer = pPlayer->AddComponent<C_QBertMovement>();
	pMovementPlayer->SetTileMap(pTileMapObj.get());
	pMovementPlayer->SetTexturePaths(std::vector<std::string>{ "qbert_0.png", "qbert_1.png", "qbert_2.png", "qbert_3.png" });
	pMovementPlayer->SetStartTile(21);
	pMovementPlayer->MoveToStartTile(true);
	pMovementPlayer->SetTileChange(C_QBertMovement::TileChange::eUpdate);
	pMovementPlayer->SetTeleports(std::vector<C_Teleport*>{ pTeleport, pTeleport2 });

	pPlayer->AddComponent<C_PlayerCollision>();

	// Player2
	auto pPlayer2 = std::make_shared<GameObject>("Player 2");
	pPlayer2->SetTag("Friendly");
	Add(pPlayer2);

	auto pLives2 = pPlayer2->AddComponent<C_Lives>();
	pLives2->SetLives(3);

	auto pHealth2 = pPlayer2->AddComponent<C_Health>();
	pHealth2->SetHealth(1);

	auto pScore2 = pPlayer2->AddComponent<C_Score>();

	auto pRenderPlayer2 = pPlayer2->AddComponent<C_Render>();
	pRenderPlayer2->SetTexture("qbert_0.png");

	auto pMovementPlayer2 = pPlayer2->AddComponent<C_QBertMovement>();
	pMovementPlayer2->SetTileMap(pTileMapObj.get());
	pMovementPlayer2->SetTexturePaths(std::vector<std::string>{ "qbert_0.png", "qbert_1.png", "qbert_2.png", "qbert_3.png" });
	pMovementPlayer2->SetStartTile(27);
	pMovementPlayer2->MoveToStartTile(true);
	pMovementPlayer2->SetTileChange(C_QBertMovement::TileChange::eUpdate);
	pMovementPlayer2->SetTeleports(std::vector<C_Teleport*>{ pTeleport, pTeleport2 });

	pPlayer2->AddComponent<C_PlayerCollision>();

	// input
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonLeft, new MoveBottomLeft{ pPlayer.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonUp, new MoveTopLeft{ pPlayer.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonRight, new MoveTopRight{ pPlayer.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(XBoxController::ControllerButton::eButtonDown, new MoveBottomRight{ pPlayer.get(), InputManager::InputKeyAction::ePressed });

	inputManager.AddInputAction(SDL_SCANCODE_A, new MoveBottomLeft{ pPlayer2.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(SDL_SCANCODE_W, new MoveTopLeft{ pPlayer2.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(SDL_SCANCODE_D, new MoveTopRight{ pPlayer2.get(), InputManager::InputKeyAction::ePressed });
	inputManager.AddInputAction(SDL_SCANCODE_S, new MoveBottomRight{ pPlayer2.get(), InputManager::InputKeyAction::ePressed });

	// UI
	std::vector<Subject*> pSubjects{ pHealth->GetUISubject(), pScore->GetSubject() };
	std::vector<Subject*> pSubjects2{ pHealth2->GetUISubject(), pScore2->GetSubject() };
	auto& uiManager = UIManager::GetInstance();
	uiManager.RemoveUILayer("PlayerUI");
	uiManager.RemoveUILayer("PlayerUI");
	uiManager.AddUILayer(new PlayerUI{ glm::vec2{ 0.0f, 0.0f }, pSubjects });
	uiManager.AddUILayer(new PlayerUI{ glm::vec2{ m_GameSettings.m_WindowWidth - 200.f, 0.0f }, pSubjects2 });

	// Coily
	auto pCoily = std::make_shared<GameObject>();
	pCoily->SetTag("Enemy");
	pCoily->SetName("Coily");
	auto pRenderCoily = pCoily->AddComponent<C_Render>();
	pRenderCoily->SetTexture("coily_0.png");
	auto pMovementCoily = pCoily->AddComponent<C_QBertMovement>();
	pMovementCoily->SetTileMap(pTileMapObj.get());
	pMovementCoily->SetTexturePaths(std::vector<std::string>{ "coily_0.png", "coily_1.png", "coily_2.png", "coily_3.png" });
	auto pCoilyController = pCoily->AddComponent<C_CoilyController>();
	pCoilyController->SetNrOfRows(nrOfRows);
	Add(pCoily);

	// Ugg
	auto pUgg = std::make_shared<GameObject>("Ugg");
	pUgg->SetTag("Enemy");
	Add(pUgg);
	auto pRenderUgg = pUgg->AddComponent<C_Render>();
	pRenderUgg->SetTexture("ugg_0.png");
	auto pMovementUgg = pUgg->AddComponent<C_QBertMovement>();
	pMovementUgg->SetTileMap(pTileMapObj.get());
	pMovementUgg->SetTexturePaths(std::vector<std::string>{ "ugg_0.png", "ugg_0.png", "ugg_1.png", "ugg_1.png" });
	pUgg->AddComponent<C_UggController>();

	// Wrongway
	auto pWrongway = std::make_shared<GameObject>("Wrongway");
	pWrongway->SetTag("Enemy");
	Add(pWrongway);
	auto pRenderwrongway = pWrongway->AddComponent<C_Render>();
	pRenderwrongway->SetTexture("ugg_0.png");
	auto pMovementWrongway = pWrongway->AddComponent<C_QBertMovement>();
	pMovementWrongway->SetTileMap(pTileMapObj.get());
	pMovementWrongway->SetTexturePaths(std::vector<std::string>{ "wrongway_1.png", "wrongway_1.png", "wrongway_0.png", "wrongway_0.png" });
	pWrongway->AddComponent<C_WrongwayController>();

	// Slick
	auto pSlick = std::make_shared<GameObject>("Slick");
	pSlick->SetTag("Catchable");
	Add(pSlick);
	auto pRenderSlick = pSlick->AddComponent<C_Render>();
	pRenderSlick->SetTexture("slick_0.png");
	auto pMovementSlick = pSlick->AddComponent<C_QBertMovement>();
	pMovementSlick->SetTexturePaths(std::vector<std::string>{ "slick_0.png", "slick_1.png", "slick_0.png", "slick_1.png" });
	pMovementSlick->SetTileMap(pTileMapObj.get());
	pMovementSlick->SetTileChange(C_QBertMovement::TileChange::eRevert);
	pSlick->AddComponent<C_SlickAndSlamController>();

	// Sam
	auto pSam = std::make_shared<GameObject>("Sam");
	pSam->SetTag("Catchable");
	Add(pSam);
	auto pRenderSam = pSam->AddComponent<C_Render>();
	pRenderSam->SetTexture("sam_0.png");
	auto pMovementSam = pSam->AddComponent<C_QBertMovement>();
	pMovementSam->SetTexturePaths(std::vector<std::string>{ "sam_0.png", "sam_1.png", "sam_0.png", "sam_1.png" });
	pMovementSam->SetTileMap(pTileMapObj.get());
	pMovementSam->SetTileChange(C_QBertMovement::TileChange::eRevert);
	pSam->AddComponent<C_SlickAndSlamController>();

	// Game Manager
	pGameObject = std::make_shared<GameObject>();
	auto pGameManager = pGameObject->AddComponent<C_GameManager>();
	pGameManager->AddSubject(pMovementPlayer->GetSubject());
	pGameManager->AddSubject(pMovementPlayer2->GetSubject());
	pGameManager->AddSubject(pMovementUgg->GetSubject());
	pGameManager->AddSubject(pMovementWrongway->GetSubject());
	pGameManager->AddSubject(pMovementCoily->GetSubject());
	pGameManager->AddSubject(pMovementSlick->GetSubject());
	pGameManager->AddSubject(pMovementSam->GetSubject());
	pGameManager->AddSubject(pHealth->GetGameManagerSubject());
	pGameManager->AddSubject(pHealth2->GetGameManagerSubject());
	pGameManager->AddSubject(pLives->GetSubject());
	pGameManager->AddSubject(pLives2->GetSubject());
	pGameManager->SpawnOverTime(pCoily.get(), 4.f);
	pGameManager->SpawnOverTime(pUgg.get(), 7.f);
	pGameManager->SpawnOverTime(pWrongway.get(), 10.f);
	pGameManager->SpawnOverTime(pSam.get(), 12.f);
	pGameManager->SpawnOverTime(pSlick.get(), 15.f);
	Add(pGameObject);
}

void dae::CoopLevel2::OnSceneEnd()
{
	auto& inputManager{ InputManager::GetInstance() };
	inputManager.RemoveInputAction(XBoxController::ControllerButton::eButtonLeft);
	inputManager.RemoveInputAction(XBoxController::ControllerButton::eButtonUp);
	inputManager.RemoveInputAction(XBoxController::ControllerButton::eButtonRight);
	inputManager.RemoveInputAction(XBoxController::ControllerButton::eButtonDown);

	inputManager.RemoveInputAction(SDL_SCANCODE_A);
	inputManager.RemoveInputAction(SDL_SCANCODE_W);
	inputManager.RemoveInputAction(SDL_SCANCODE_D);
	inputManager.RemoveInputAction(SDL_SCANCODE_S);

	auto& sceneManager{ SceneManager::GetInstance() };
	MarkForRestart();
	sceneManager.GetScene(6)->CreateScene();
	sceneManager.SetScene(6);
}

void dae::CoopLevel2::CreateTilePositions(std::vector<glm::vec3>& tilePositions, float tileSize, int nrOfRows)
{
	glm::vec2 startRowPos{ m_GameSettings.m_WindowWidth / 2 - tileSize / 2, 10.f };
	glm::vec2 tilePos{ startRowPos };
	for (int i{}; i < nrOfRows; ++i)
	{
		for (int j{}; j < (i + 1); ++j)
		{
			tilePositions.push_back(glm::vec3{ tilePos.x, tilePos.y, 1.0f });
			tilePos.x += tileSize;
		}

		startRowPos.x -= tileSize / 2;
		startRowPos.y += tileSize * 0.75f;
		tilePos = startRowPos;
	}
}