#ifndef _3FENGINE_SRC_F_MOUSE_EVENT_HPP_
#define _3FENGINE_SRC_F_MOUSE_EVENT_HPP_

#include <utils/f_flags.hpp>
#include <events/f_event.hpp>
#include <events/f_events_enums.hpp>
#include <utils/f_typedefs.hpp>

namespace fengine 
{
	class FMouseEvent : public FEvent
	{
	public:

		explicit FMouseEvent(EventType type, const FPoint2i& pos, MouseButton button, const MouseButtons& buttons, const KeyboardModifiers& modifiers);

		virtual ~FMouseEvent() {}

		const FPoint2i& pos() const noexcept { return this->pos_; }

		MouseButton button() const noexcept { this->button_; }

		const MouseButtons& buttons() const noexcept { this->buttons_; }

		const KeyboardModifiers& modifiers() const noexcept { this->modifiers_; }

	private:
		FPoint2i pos_;
		MouseButton button_;
		MouseButtons buttons_;
		KeyboardModifiers modifiers_;
	};
}

#endif // _3FENGINE_SRC_F_MOUSE_EVENT_HPP_