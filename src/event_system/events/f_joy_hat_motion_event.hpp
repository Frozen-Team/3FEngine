#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_HAT_MOTION_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_HAT_MOTION_EVENT_HPP_

#include <event_system/events/f_event.hpp>

namespace fengine
{
	class FJoyHatMotionEvent : public FEvent
	{
	public:
		explicit FJoyHatMotionEvent(unsigned which, unsigned hat, int value);

		unsigned hat() const noexcept { return hat_; }

		int value() const noexcept { return value_; }

	private:
		unsigned hat_;
		int value_;
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_HAT_MOTION_EVENT_HPP_