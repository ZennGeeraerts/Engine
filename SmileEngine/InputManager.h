#pragma once
#include "Singleton.h"
#include "XBoxController.h"
#include <map>
#include "SDLInputSystem.h"

namespace dae
{
	class InputCommand;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		enum class InputKeyAction
		{
			ePressed,
			eReleased,
			eDown
		};

		~InputManager();
		bool ProcessInput();

		bool IsPressed(XBoxController::ControllerButton button) const;
		bool IsDown(XBoxController::ControllerButton button) const;
		bool IsDown(SDL_Scancode button);
		bool IsReleased(XBoxController::ControllerButton button) const;

		void AddInputAction(XBoxController::ControllerButton button, InputCommand* pCommand);
		void AddInputAction(SDL_Scancode button, InputCommand* pCommand);
		
	private:
		bool HandleInput();
		bool CheckCommandExecution(const std::pair<XBoxController::ControllerButton, InputCommand*>& commandPair) const;

		XBoxController m_Controller{ 0 };
		SDLInputSystem m_InputSystem;
		std::map<XBoxController::ControllerButton, InputCommand*> m_ControllerCommandsMap;
		std::map<SDL_Scancode, InputCommand*> m_KeyboardCommandsMap;
	};
}