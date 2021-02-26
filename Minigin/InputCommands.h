#pragma once
#include "InputManager.h"

namespace dae
{
	class GameObject;

	class InputCommand
	{
	public:
		InputCommand(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		virtual ~InputCommand() = default;
		virtual bool Execute() = 0;
		InputManager::InputKeyAction GetInputKeyAction() const;
	protected:
		GameObject* m_pGameObject;

	private:
		InputManager::InputKeyAction m_InputKeyAction;
	};

	class Quit final : public InputCommand
	{
	public:
		Quit(InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};

	class PlayerDie : public InputCommand
	{
	public:
		PlayerDie(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};
}
