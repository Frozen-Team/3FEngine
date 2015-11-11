#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_HAT_MOTION_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_HAT_MOTION_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_device_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyHatMotionListener : public FEventListener
	{
	public:
		FJoyHatMotionListener() : FEventListener(fevents::EventSourceTypes(fevents::kJoystickSource)) {};

		virtual ~FJoyHatMotionListener() = default;

	protected:
		friend class FEventsManager;

		virtual void OnJoyHatMotion(FJoyDeviceEvent& e) {};

		virtual void CallEvent(FJoyDeviceEvent& e)
		{
			switch (e.type())
			{
			case fevents::kJoyHatMotion:
				OnJoyHatMotion(e);
				break;
			default:
				break;
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_HAT_MOTION_LISTENER_HPP_