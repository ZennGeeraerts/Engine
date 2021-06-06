#include "Input.h"
#include "GameObject.h"
#include "C_Health.h"
#include "C_Score.h"
#include "C_QBertMovement.h"

#include "ServiceLocator.h"

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

	ServiceLocator::GetSoundSystem().Play(0, 100, "../Data/jump.wav");

	return true;
}

// MoveBottomLeft
dae::MoveBottomLeft::MoveBottomLeft(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveBottomLeft::Execute()
{
	if (!m_pGameObject)
	{
		return true;
	}

	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	if (pMovement)
	{
		pMovement->MoveBottomLeft();
	}
	return true;
}

// MoveTopRight
dae::MoveTopRight::MoveTopRight(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveTopRight::Execute()
{
	if (!m_pGameObject)
	{
		return true;
	}

	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	if (pMovement)
	{
		pMovement->MoveTopRight();
	}
	return true;
}

// MoveBottomRight
dae::MoveBottomRight::MoveBottomRight(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveBottomRight::Execute()
{
	if (!m_pGameObject)
	{
		return true;
	}

	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	if (pMovement)
	{
		pMovement->MoveBottomRight();
	}
	return true;
}

// MoveTopLeft
dae::MoveTopLeft::MoveTopLeft(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction)
	: InputCommand(pGameObject, inputKeyAction)
{

}

bool dae::MoveTopLeft::Execute()
{
	if (!m_pGameObject)
	{
		return true;
	}

	C_QBertMovement* pMovement = m_pGameObject->GetComponent<C_QBertMovement>();
	if (pMovement)
	{
		pMovement->MoveTopLeft();
	}
	return true;
}