#include "SmileEnginePCH.h"
#include "InputCommands.h"
#include "GameObject.h"
#include "C_Health.h"
#include "C_Score.h"
#include "C_QBertMovement.h"

#include "ServiceLocator.h"

dae::InputCommand::InputCommand(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: m_pGameObject{ pGameObject }
	, m_InputKeyAction{ inputKeyAction }
{

}

dae::InputManager::InputKeyAction dae::InputCommand::GetInputKeyAction() const
{
	return m_InputKeyAction;
}

// Quit
dae::Quit::Quit(InputManager::InputKeyAction inputKeyAction)
	: InputCommand(nullptr, inputKeyAction)
{
	
}

bool dae::Quit::Execute()
{
	return false;
}

// PlayerDie
dae::PlayerDie::PlayerDie(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::PlayerDie::Execute()
{
	auto pHealth = m_pGameObject->GetComponent<C_Health>();
	if (pHealth)
	{
		pHealth->Kill();
	}

	return true;
}


// ScoreIncrease
dae::ScoreIncrease::ScoreIncrease(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::ScoreIncrease::Execute()
{
	auto pScore = m_pGameObject->GetComponent<C_Score>();
	if (pScore)
	{
		pScore->IncreaseScore(50);
	}

	ServiceLocator::GetSoundSystem().Play(0, 100, "../Data/jump.wav" );

	return true;
}

// MoveBottomLeft
dae::MoveBottomLeft::MoveBottomLeft(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveBottomLeft::Execute()
{
	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	pMovement->MoveBottomLeft();
	return true;
}

// MoveTopRight
dae::MoveTopRight::MoveTopRight(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveTopRight::Execute()
{
	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	pMovement->MoveTopRight();
	return true;
}

// MoveBottomRight
dae::MoveBottomRight::MoveBottomRight(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveBottomRight::Execute()
{
	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	pMovement->MoveBottomRight();
	return true;
}

// MoveTopLeft
dae::MoveTopLeft::MoveTopLeft(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveTopLeft::Execute()
{
	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	pMovement->MoveTopLeft();
	return true;
}
