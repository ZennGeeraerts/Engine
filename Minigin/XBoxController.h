#pragma once
#include <Windows.h>
#include <Xinput.h>

namespace dae
{
	class XBoxController final
	{
	public:
		enum class ControllerButton
		{
			eButtonUp,
			eButtonDown,
			eButtonLeft,
			eButtonRight,
			eStart,
			eBack,
			eLeftThumb,
			eRightThumb,
			eLeftShoulder,
			eRightShoulder,
			eButtonA,
			eButtonB,
			eButtonX,
			eButtonY,
			eNrOfButtons
		};

		XBoxController(int index);

		void ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsDown(ControllerButton button) const;
		bool IsReleased(ControllerButton button) const;

	private:
		int m_Index;
		XINPUT_STATE m_CurrentState;
		XINPUT_STATE m_PreviousState;
		int m_ButtonMasks[int(ControllerButton::eNrOfButtons)]
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

