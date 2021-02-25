#include "InputCommands.h"

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