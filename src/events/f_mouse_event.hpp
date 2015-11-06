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

		explicit FMouseEvent(fevents::EventType type, const FPoint2i& pos, fevents::MouseButton button, const fevents::MouseButtons& buttons, const fevents::KeyboardModifiers& modifiers);

		virtual ~FMouseEvent() {}

		const FPoint2i& pos() const noexcept { return this->pos_; }

		fevents::MouseButton button() const noexcept { this->button_; }

		const fevents::MouseButtons& buttons() const noexcept { this->buttons_; }

		const fevents::KeyboardModifiers& modifiers() const noexcept { this->modifiers_; }

	private:
		FPoint2i pos_;
		fevents::MouseButton button_;
		fevents::MouseButtons buttons_;
		fevents::KeyboardModifiers modifiers_;
	};
}

#endif // _3FENGINE_SRC_F_MOUSE_EVENT_HPP_