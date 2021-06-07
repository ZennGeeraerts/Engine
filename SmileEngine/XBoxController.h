#pragma once

namespace dae
{
	class XBoxControllerImpl;

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
		~XBoxController() noexcept;
		XBoxController(const XBoxController& other) = delete;
		XBoxController(XBoxController&& other) noexcept = delete;
		XBoxController& operator=(const XBoxController& other) = delete;
		XBoxController& operator=(XBoxController&& other) noexcept = delete;

		void ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsDown(ControllerButton button) const;
		bool IsReleased(ControllerButton button) const;

	private:
		XBoxControllerImpl* m_pImpl;
	};
}

