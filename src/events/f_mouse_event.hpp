#ifndef _3FENGINE_SRC_F_MOUSE_EVENT_HPP_
#define _3FENGINE_SRC_F_MOUSE_EVENT_HPP_

#include <utils/f_flags.hpp>
#include <events/f_event.hpp>
#include <utils/f_typedefs.hpp>

namespace fengine {
	class FMouseEvent : public FEvent
	{
	public:
		enum MouseButton
		{
			kNoButton = 0,
			kLeftButton = 1,
			kMiddleButton = 2,
			kRightButton = 4,
			kXButton1 = 8,
			kXButton2 = 16
		};

		F_DECLARE_FLAGS_ENUM(MouseButton, MouseButtons)

		explicit FMouseEvent(EventType type, const FPoint2i& pos, MouseButton button, const MouseButtons& buttons);

		const FPoint2i& pos() const noexcept { return this->pos_; }

		MouseButton button() const noexcept { this->button_; }

		const MouseButtons& buttons() const noexcept { this->buttons_; }

	private:
		FPoint2i pos_;
		MouseButton button_;
		MouseButtons buttons_;
	};
}

#endif // _3FENGINE_SRC_F_MOUSE_EVENT_HPP_