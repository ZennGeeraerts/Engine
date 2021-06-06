#pragma once
#include "InputCommands.h"

namespace dae
{
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
