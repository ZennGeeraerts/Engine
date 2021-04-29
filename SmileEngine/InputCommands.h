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

	class ScoreIncrease : public InputCommand
	{
	public:
		ScoreIncrease(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};

	class MoveBottomLeft : public InputCommand
	{
	public:
		MoveBottomLeft(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};

	class MoveTopRight : public InputCommand
	{
	public:
		MoveTopRight(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};

	class MoveBottomRight : public InputCommand
	{
	public:
		MoveBottomRight(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};

	class MoveTopLeft : public InputCommand
	{
	public:
		MoveTopLeft(GameObject* pGameObject, InputManager::InputKeyAction inputKeyAction);
		bool Execute() override;
	};
}
