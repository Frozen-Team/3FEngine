#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_MOUSE_WHEEL_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_MOUSE_WHEEL_EVENT_HPP_

#include <event_system/events/f_event.hpp>
#include <event_system/events/f_events_enums.hpp>
#include <utils/f_typedefs.hpp>

namespace fengine
{
	class FMouseWheelEvent : public FEvent
	{
	public:
		
		explicit FMouseWheelEvent(int delta, unsigned which, const FPoint2i& position, const fevents::MouseButtons& buttons,
			fevents::KeyboardModifiers modifiers, fevents::WheelOrientation orientation = fevents::WheelOrientation::kWheelVertical);

		virtual ~FMouseWheelEvent() {}

		int delta() const noexcept { return this->delta_; }

		const FPoint2i& pos() const noexcept { return this->pos_; }

		const fevents::MouseButtons& buttons() const noexcept { return this->buttons_; }

		const fevents::KeyboardModifiers& modifiers() const noexcept { return this->modifiers_; }

		fevents::WheelOrientation orientation() const noexcept { return this->orientation_; }

	private:
		int delta_;
		FPoint2i pos_;
		fevents::MouseButtons buttons_;
		fevents::KeyboardModifiers modifiers_;
		fevents::WheelOrientation orientation_;
	};

}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_MOUSE_WHEEL_EVENT_HPP_