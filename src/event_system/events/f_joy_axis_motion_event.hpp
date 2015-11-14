#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOYSTICK_AXIS_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOYSTICK_AXIS_EVENT_HPP_

#include <event_system/events/f_event.hpp>

namespace fengine
{
	class FJoyAxisMotionEvent : public FEvent
	{
	public:
		explicit FJoyAxisMotionEvent(unsigned which, unsigned axis, int value);

	private:
		unsigned axis_;
		int value_;	
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOYSTICK_AXIS_EVENT_HPP_