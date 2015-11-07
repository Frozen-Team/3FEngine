#include "f_joy_device_event.hpp"

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	FJoyDeviceEvent::FJoyDeviceEvent(fevents::EventType type, unsigned which)
		: FEvent(type, which)
	{
		LOG_IF(type != fevents::EventType::kJoyDeviceAdded && type != fevents::EventType::kJoyDeviceRemoved, FATAL) << "Invalid joystick device event type: " << type;
	}
}
