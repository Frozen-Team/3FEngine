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

		virtual void OnJoyHatMotion(FJoyHatMotionEvent& e) {};

		virtual void CallEvent(FJoyHatMotionEvent& e)
		{
			if (e.type() == fevents::kJoyHatMotion)
			{
				OnJoyHatMotion(e);
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_HAT_MOTION_LISTENER_HPP_