#include "SmileEnginePCH.h"
#include "XBoxControllerImpl.h"

dae::XBoxControllerImpl::XBoxControllerImpl(int index)
	: m_Index{ index }
	, m_CurrentState{}
	, m_PreviousState{}
{

}

void dae::XBoxControllerImpl::ProcessInput()
{
	CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(m_Index, &m_CurrentState); // 0 = controller index
}

bool dae::XBoxControllerImpl::IsPressed(XBoxController::ControllerButton button) const
{
	if (m_CurrentState.Gamepad.wButtons == m_PreviousState.Gamepad.wButtons)
	{
		return false;
	}

	return IsDown(button);
}

bool dae::XBoxControllerImpl::IsDown(XBoxController::ControllerButton button) const
{
	return (m_CurrentState.Gamepad.wButtons & m_ButtonMasks[int(button)]) != 0;
}

bool dae::XBoxControllerImpl::IsReleased(XBoxController::ControllerButton button) const
{
	if (m_CurrentState.Gamepad.wButtons == m_PreviousState.Gamepad.wButtons)
	{
		return false;
	}

	return (m_PreviousState.Gamepad.wButtons & m_ButtonMasks[int(button)]) != 0;
}