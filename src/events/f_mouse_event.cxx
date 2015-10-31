#include "f_mouse_event.hpp"
#include <components/f_logger.hpp>

fengine::FMouseEvent::FMouseEvent(EventType type, const FPoint2i & pos, MouseButton button, const MouseButtons& buttons, const KeyboardModifiers& modifiers)
	: FEvent(type), pos_(pos), button_(button), buttons_(buttons), modifiers_(modifiers)
{
	LOG_IF((type != kMouseMove) || (type != kMouseButtonDblClick) || (type != kMouseButtonPress) ||
		(type != kMouseButtonRelease), FATAL) << "Invalid mouse event type: " << type;
}
