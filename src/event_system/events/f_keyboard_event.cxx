#include "f_keyboard_event.hpp"

namespace fengine
{
	FKeyboardEvent::FKeyboardEvent(fevents::EventType type, unsigned which, fevents::KeyboardKey key, fevents::KeyboardModifiers modifiers)
		: FEvent(type, which), key_(key), modifiers_(modifiers)
	{
		LOG_IF((type != fevents::kKeyPress) && (type != fevents::kKeyRelease), FATAL) << "Invalid keyboard event type."; // TODOL Print type
	}
}