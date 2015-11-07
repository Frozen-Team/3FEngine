#include "f_joy_hat_motion_event.hpp"

namespace fengine
{
	FJoyHatMotionEvent::FJoyHatMotionEvent(unsigned which, unsigned hat, int value)
		: FEvent(fevents::EventType::kJoyHatMotion, which), hat_(hat), value_(value_)
	{}
}