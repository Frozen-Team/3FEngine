#include "f_mouse_wheel_event.hpp"

namespace fengine
{
	FMouseWheelEvent::FMouseWheelEvent(int delta, const FPoint2i & pos, const MouseButtons & buttons, KeyboardModifiers modifiers, WheelOrientation orientation)
		: FEvent(FEvent::kMouseWheel), delta_(delta), pos_(pos), buttons_(buttons), modifiers_(modifiers), orientation_(orientation)
	{}
}