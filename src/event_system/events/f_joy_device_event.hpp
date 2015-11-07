#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_DEVICE_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_DEVICE_EVENT_HPP_

#include <event_system/events/f_event.hpp>

namespace fengine
{
	class FJoyDeviceEvent : public FEvent
	{
	public:
		explicit FJoyDeviceEvent(fevents::EventType type, unsigned which);
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_DEVICE_EVENT_HPP_