#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_MOUSE_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_MOUSE_EVENT_HPP_

#include <utils/f_flags.hpp>
#include <event_system/events/f_event.hpp>
#include <event_system/events/f_events_enums.hpp>
#include <utils/f_typedefs.hpp>

namespace fengine 
{
	class FMouseEvent : public FEvent
	{
	public:
		explicit FMouseEvent(fevents::EventType type, unsigned which, const FPoint2i& pos, fevents::MouseButton button, const fevents::MouseButtons& buttons, const fevents::KeyboardModifiers& modifiers);
		
		virtual ~FMouseEvent() {}

		const FPoint2i& pos() const noexcept { return this->pos_; }

		fevents::MouseButton button() const noexcept { return this->button_; }

		const fevents::MouseButtons& buttons() const noexcept { return this->buttons_; }

		const fevents::KeyboardModifiers& modifiers() const noexcept { return this->modifiers_; }

	private:
		FPoint2i pos_;
		fevents::MouseButton button_;
		fevents::MouseButtons buttons_;
		fevents::KeyboardModifiers modifiers_;
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_MOUSE_EVENT_HPP_