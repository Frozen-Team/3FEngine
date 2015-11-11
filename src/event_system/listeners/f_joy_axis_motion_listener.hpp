#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_AXIS_MOTION_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_AXIS_MOTION_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_axis_motion_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyAxisMotionListener : public FEventListener
	{
	public:
		FJoyAxisMotionListener() : FEventListener(fevents::EventSourceTypes(fevents::kJoystickSource)) {};

		virtual ~FJoyAxisMotionListener() = default;

	protected:
		friend class FEventsManager;

		virtual void OnJoyAxisMotion(FJoyAxisMotionEvent& e) {};

		virtual void CallEvent(FJoyAxisMotionEvent& e)
		{
			switch (e.type())
			{
			case fevents::kJoyAxisMotion:
				OnJoyAxisMotion(e);
				break;
			default:
				break;
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_AXIS_MOTION_LISTENER_HPP_