#include "f_mouse_wheel_event.hpp"
#include <fcomponents/f_logger.hpp>

namespace fengine
{
	FMouseWheelEvent::FMouseWheelEvent(int delta, const FPoint2i & pos, const fevents::MouseButtons & buttons, fevents::KeyboardModifiers modifiers, fevents::WheelOrientation orientation)
		: FEvent(fevents::kMouseWheel), delta_(delta), pos_(pos), buttons_(buttons), modifiers_(modifiers), orientation_(orientation)
	{
		// TODO: Check type check
	}
}