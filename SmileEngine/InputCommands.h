#pragma once
#include "InputManager.h"

namespace dae
{
	class GameObject;

	class InputCommand
	{
	public:
		InputCommand(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		virtual ~InputCommand() noexcept = default;

		InputCommand(const InputCommand& other) = delete;
		InputCommand(InputCommand&& other) noexcept = delete;
		InputCommand& operator=(const InputCommand& other) = delete;
		InputCommand& operator=(InputCommand&& other) noexcept = delete;

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
}
