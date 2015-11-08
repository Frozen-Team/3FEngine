#include "f_joy_axis_motion_event.hpp"

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	FJoyAxisMotionEvent::FJoyAxisMotionEvent(fevents::EventType type, unsigned which, unsigned axis, int value)
		: FEvent(type, which), axis_(axis), value_(value)
	{
		LOG_IF(type != fevents::kJoyAxisMotion, FATAL) << "Invalid joystick axis motion event. Type: " << type;
	}
}
