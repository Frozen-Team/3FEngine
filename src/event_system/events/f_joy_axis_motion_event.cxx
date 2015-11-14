#include "f_joy_axis_motion_event.hpp"

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	FJoyAxisMotionEvent::FJoyAxisMotionEvent(unsigned which, unsigned axis, int value)
		: FEvent(fevents::kJoyAxisMotion, which), axis_(axis), value_(value)
	{}
}
