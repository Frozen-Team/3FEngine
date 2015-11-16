#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BALL_MOTION_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BALL_MOTION_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_ball_motion_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyBallMotionListener : virtual public FEventListener
	{
		friend class FEventsManager;
	public:
		FJoyBallMotionListener() { SetListenableSource(fevents::kJoyBallSource); };

		virtual ~FJoyBallMotionListener() = default;

	protected:
		virtual void OnJoyBallMotion(FJoyBallMotionEvent& e) {};

		virtual void CallEvent(FJoyBallMotionEvent& e)
		{
			if (e.type() == fevents::kJoyBallMotion)
			{
				OnJoyBallMotion(e);
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BALL_MOTION_LISTENER_HPP_