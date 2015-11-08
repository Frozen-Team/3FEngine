#include "f_joy_button_event.hpp"

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	FJoyButtonEvent::FJoyButtonEvent(fevents::EventType type, unsigned which, unsigned button)
		: FEvent(type, which), button_(button)
	{
		LOG_IF(type != fevents::kJoyButtonDown && type != fevents::kJoyButtonUp, FATAL) << "Invalid joystick button event type: " << type;
	}
}
