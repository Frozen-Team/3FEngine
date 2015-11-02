#include "f_mouse_event.hpp"
#include <fcomponents/f_logger.hpp>

namespace fengine 
{
	FMouseEvent::FMouseEvent(EventType type, const FPoint2i & pos, MouseButton button, const MouseButtons& buttons, const KeyboardModifiers& modifiers)
		: FEvent(type), pos_(pos), button_(button), buttons_(buttons), modifiers_(modifiers)
	{
		LOG_IF((type != EventType::kMouseMove) /*|| (type != EventType::kMouseButtonDblClick)*/ || (type != EventType::kMouseButtonPress) ||
				(type != EventType::kMouseButtonRelease), FATAL) << "Invalid mouse event type."; // TODO: Print type info
	}

}
