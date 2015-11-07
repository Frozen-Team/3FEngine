#include "f_mouse_event.hpp"
#include <fcomponents/f_logger.hpp>

namespace fengine 
{
	FMouseEvent::FMouseEvent(fevents::EventType type, unsigned which, const FPoint2i & pos, fevents::MouseButton button, const fevents::MouseButtons& buttons, const fevents::KeyboardModifiers& modifiers)
		: FEvent(type, which), pos_(pos), button_(button), buttons_(buttons), modifiers_(modifiers)
	{
		LOG_IF((type != fevents::kMouseMove) && (type != fevents::kMouseButtonPress) &&
				(type != fevents::kMouseButtonRelease), FATAL) << "Invalid mouse event type."; // TODO: Print type info
	}

}
