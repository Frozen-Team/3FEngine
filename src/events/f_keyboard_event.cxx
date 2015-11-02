#include "f_keyboard_event.hpp"

namespace fengine
{
	FKeyboardEvent::FKeyboardEvent(EventType type, KeyboardKey key, KeyboardModifiers modifiers)
		: FEvent(type), key_(key), modifiers_(modifiers)
	{
		//LOG_IF((type != EventType::kKeyPress) || (type != EventType::kKeyRelease), FATAL) << "Invalid keyboard event type."; // TODOL Print type
	}
}
