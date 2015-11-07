#include "f_joy_ball_motion_event.hpp"

namespace fengine
{
	FBJoyBallMotionEvent::FBJoyBallMotionEvent(unsigned which, unsigned ball, const FPoint2i& delta)
		: FEvent(fevents::EventType::kJoyBallMotion, which), ball_(ball), delta_(delta)
	{}
}
