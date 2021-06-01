#include "SmileEnginePCH.h"
#include "InputManager.h"
#include "InputCommands.h"
#include <SDL.h>

dae::InputManager::~InputManager()
{
	for (auto& command : m_ControllerCommandsMap)
	{
		delete command.second;
	}

	m_ControllerCommandsMap.clear();
	
	for (auto& command : m_KeyboardCommandsMap)
	{
		delete command.second;
	}

	m_KeyboardCommandsMap.clear();
}

bool dae::InputManager::ProcessInput()
{
	m_Controller.ProcessInput();
	m_InputSystem.ProcessInput();
	return HandleInput();
}

bool dae::InputManager::HandleInput()
{
	if (!m_InputSystem.HandleInput())
	{
		return false;
	}

	for (auto& command : m_ControllerCommandsMap)
	{
		if (CheckCommandExecution(command))
		{
			if (!command.second->Execute())
			{
				return false;
			}
		}
	}

	for (auto& command : m_KeyboardCommandsMap)
	{
		if (IsDown(command.first))
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

bool dae::InputManager::IsDown(SDL_Scancode button) const
{
	return m_InputSystem.IsDown(button);
}

bool dae::InputManager::IsReleased(XBoxController::ControllerButton button) const
{
	return m_Controller.IsReleased(button);
}

void dae::InputManager::AddInputAction(XBoxController::ControllerButton button, InputCommand* pCommand)
{
	auto it = std::find_if(m_ControllerCommandsMap.begin(), m_ControllerCommandsMap.end(),
		[button](const auto& command) 
		{
			return command.first == button;
		}
	);

	if (it != m_ControllerCommandsMap.end())
	{
		delete (*it).second;
		m_ControllerCommandsMap.erase(button);
	}

	m_ControllerCommandsMap[button] = pCommand;
}

void dae::InputManager::AddInputAction(SDL_Scancode button, InputCommand* pCommand)
{
	auto it = std::find_if(m_KeyboardCommandsMap.begin(), m_KeyboardCommandsMap.end(),
		[button](const auto& command)
		{
			return command.first == button;
		}
	);

	if (it != m_KeyboardCommandsMap.end())
	{
		delete (*it).second;
		m_KeyboardCommandsMap.erase(button);
	}

	m_KeyboardCommandsMap[button] = pCommand;
}
