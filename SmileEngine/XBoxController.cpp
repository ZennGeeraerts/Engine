#include "SmileEnginePCH.h"
#include "XBoxController.h"
#include "XBoxControllerImpl.h"

dae::XBoxController::XBoxController(int index)
	: m_pImpl{ new XBoxControllerImpl{ index } }
{

}

dae::XBoxController::~XBoxController() noexcept
{
	delete m_pImpl;
}

void dae::XBoxController::ProcessInput()
{
	m_pImpl->ProcessInput();
}

bool dae::XBoxController::IsPressed(ControllerButton button) const
{
	return m_pImpl->IsPressed(button);
}

bool dae::XBoxController::IsDown(ControllerButton button) const
{
	return m_pImpl->IsDown(button);
}

bool dae::XBoxController::IsReleased(ControllerButton button) const
{
	return m_pImpl->IsReleased(button);
}
