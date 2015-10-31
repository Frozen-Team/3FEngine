#include "f_keyboard_event.hpp"

namespace fengine
{
	FKeyboardEvent::FKeyboardEvent(EventType type, KeyboardKey key, KeyboardModifiers modifiers)
		: FEvent(type), key_(key), modifiers_(modifiers)
	{}
}
