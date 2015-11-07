#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_BUTTON_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_BUTTON_EVENT_HPP_

#include <event_system/events/f_event.hpp>

namespace fengine
{
	class FJoyButtonEvent : public FEvent
	{
	public:
		explicit FJoyButtonEvent(fevents::EventType type, unsigned which, unsigned button);

		unsigned button() const noexcept { return button_; }

	private:
		unsigned button_;
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_BUTTON_EVENT_HPP_