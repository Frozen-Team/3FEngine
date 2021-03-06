#include "f_mouse_wheel_event.hpp"
#include <fcomponents/f_logger.hpp>

namespace fengine
{
	FMouseWheelEvent::FMouseWheelEvent(const FPoint2i& delta, unsigned which, const FPoint2i & pos, const fevents::MouseButtons & buttons, fevents::KeyboardModifiers modifiers)
		: FEvent(fevents::kMouseWheel, which), delta_(delta), pos_(pos), buttons_(buttons), modifiers_(modifiers)
	{}
}