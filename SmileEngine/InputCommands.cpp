#include "SmileEnginePCH.h"
#include "InputCommands.h"
#include "GameObject.h"
#include "C_Health.h"
#include "C_Score.h"

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

	return true;
}
