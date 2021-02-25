#include "InputManager.h"
#include "InputCommands.h"

dae::InputManager::~InputManager()
{
	for (auto& command : m_CommandsMap)
	{
		delete command.second;
	}

	m_CommandsMap.clear();
}

bool dae::InputManager::ProcessInput()
{
	m_Controller.ProcessInput();
	return HandleInput();
}

bool dae::InputManager::HandleInput()
{
	for (auto& command : m_CommandsMap)
	{
		if (CheckCommandExecution(command))
		{
			if (!command.second->Execute())
			{
				return false;
			}
		}
	}

	return true;
}

bool dae::InputManager::CheckCommandExecution(const std::pair<XBoxController::ControllerButton, InputCommand*>& commandPair) const
{
	switch (commandPair.second->GetInputKeyAction())
	{
	case InputKeyAction::ePressed:
		return IsPressed(commandPair.first);
		break;
	case InputKeyAction::eReleased:
		return IsReleased(commandPair.first);
		break;
	case InputKeyAction::eDown:
		return IsDown(commandPair.first);
		break;
	}

	return false;
}

bool dae::InputManager::IsPressed(XBoxController::ControllerButton button) const
{
	return m_Controller.IsPressed(button);
}

bool dae::InputManager::IsDown(XBoxController::ControllerButton button) const
{
	return m_Controller.IsDown(button);
}

bool dae::InputManager::IsReleased(XBoxController::ControllerButton button) const
{
	return m_Controller.IsReleased(button);
}

void dae::InputManager::AddInputAction(XBoxController::ControllerButton button, InputCommand* pCommand)
{
	m_CommandsMap[button] = pCommand;
}
