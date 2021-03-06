#pragma once
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "XInput.lib")

#include "XBoxController.h"

namespace dae
{
	class XBoxControllerImpl final
	{
	public:
		XBoxControllerImpl(int index);

		void ProcessInput();
		bool IsPressed(XBoxController::ControllerButton button) const;
		bool IsDown(XBoxController::ControllerButton button) const;
		bool IsReleased(XBoxController::ControllerButton button) const;

	private:
		int m_Index;
		XINPUT_STATE m_CurrentState;
		XINPUT_STATE m_PreviousState;
		int m_ButtonMasks[int(XBoxController::ControllerButton::eNrOfButtons)]
		{
			XINPUT_GAMEPAD_DPAD_UP,
			XINPUT_GAMEPAD_DPAD_DOWN,
			XINPUT_GAMEPAD_DPAD_LEFT,
			XINPUT_GAMEPAD_DPAD_RIGHT,
			XINPUT_GAMEPAD_START,
			XINPUT_GAMEPAD_BACK,
			XINPUT_GAMEPAD_LEFT_THUMB,
			XINPUT_GAMEPAD_RIGHT_THUMB,
			XINPUT_GAMEPAD_LEFT_SHOULDER,
			XINPUT_GAMEPAD_RIGHT_SHOULDER,
			XINPUT_GAMEPAD_A,
			XINPUT_GAMEPAD_B,
			XINPUT_GAMEPAD_X,
			XINPUT_GAMEPAD_Y
		};
	};
}

