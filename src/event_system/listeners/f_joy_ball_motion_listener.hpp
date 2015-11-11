#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BALL_MOTION_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BALL_MOTION_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_ball_motion_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyBallMotionListener : public FEventListener
	{
	public:
		FJoyBallMotionListener() : FEventListener(fevents::EventSourceTypes(fevents::kJoystickSource)) {};

		virtual ~FJoyBallMotionListener() = default;

	protected:
		friend class FEventsManager;

		virtual void OnJoyBallMotion(FJoyBallMotionEvent& e) {};

		virtual void CallEvent(FJoyBallMotionEvent& e)
		{
			switch (e.type())
			{
			case fevents::kJoyBallMotion:
				OnJoyBallMotion(e);
				break;
			default:
				break;
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BALL_MOTION_LISTENER_HPP_