#ifndef _3FENGINE_SRC_F_MOUSE_WHEEL_EVENT_HPP_
#define _3FENGINE_SRC_F_MOUSE_WHEEL_EVENT_HPP_

#include <components/f_logger.hpp>
#include <events/f_event.hpp>
#include <events/f_events_enums.hpp>
#include <utils/f_typedefs.hpp>
#include <events/f_mouse_event.hpp>
#include <events/f_keyboard_event.hpp>

namespace fengine
{
	class FMouseWheelEvent : public FEvent
	{
	public:
		
		explicit FMouseWheelEvent(int delta, const FPoint2i& position, const MouseButtons& buttons, 
			KeyboardModifiers modifiers, WheelOrientation orientation = WheelOrientation::kWheelVertical);

		int delta() const noexcept { return this->delta_; }

		const FPoint2i& pos() const noexcept { return this->pos_; }

		const MouseButtons& buttons() const noexcept { return this->buttons_; }

		const KeyboardModifiers& modifiers() const noexcept { return this->modifiers_; }

		WheelOrientation orientation() const noexcept { return this->orientation_; }

	private:
		int delta_;
		FPoint2i pos_;
		MouseButtons buttons_;
		KeyboardModifiers modifiers_;
		WheelOrientation orientation_;
	};

}
#endif // _3FENGINE_SRC_F_MOUSE_WHEEL_EVENT_HPP_