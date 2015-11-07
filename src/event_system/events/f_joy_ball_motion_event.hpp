#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_BALL_MOTION_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_BALL_MOTION_HPP_

#include <event_system/events/f_event.hpp>

namespace fengine
{
	class FBJoyBallMotionEvent : public FEvent
	{
	public:
		explicit FBJoyBallMotionEvent(unsigned which, unsigned ball, const FPoint2i& delta);

		unsigned ball() const noexcept { return ball_; }
		
		const FPoint2i& delta() const noexcept { return delta_; }

	private:
		unsigned ball_;
		FPoint2i delta_;
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_JOY_BALL_MOTION_HPP_