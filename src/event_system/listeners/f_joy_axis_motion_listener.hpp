#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_AXIS_MOTION_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_AXIS_MOTION_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_axis_motion_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyAxisMotionListener : virtual public FEventListener
	{
		friend class FEventsManager;
	public:
		FJoyAxisMotionListener() { SetListenableSource(fevents::kJoyAxisSource); };

		virtual ~FJoyAxisMotionListener() = default;

	protected:
		virtual void OnJoyAxisMotion(FJoyAxisMotionEvent& e) {};

		virtual void CallEvent(FJoyAxisMotionEvent& e)
		{
			if (e.type() == fevents::kJoyAxisMotion)
			{
				OnJoyAxisMotion(e);
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_AXIS_MOTION_LISTENER_HPP_