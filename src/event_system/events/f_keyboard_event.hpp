#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_KEYBOARD_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_KEYBOARD_EVENT_HPP_

#include <event_system/events/f_event.hpp>
#include <utils/f_flags.hpp>
#include <event_system/events/f_events_enums.hpp>

namespace fengine 
{
	class FKeyboardEvent : public FEvent
	{
	public:
		explicit FKeyboardEvent(fevents::EventType type, unsigned which, fevents::KeyboardKey key, fevents::KeyboardModifiers modifiers);

		virtual ~FKeyboardEvent() {}

		fevents::KeyboardKey key() const noexcept { return this->key_; }

		const fevents::KeyboardModifiers& modifiers() const noexcept { return this->modifiers_; }

	private:
		fevents::KeyboardKey key_;
		fevents::KeyboardModifiers modifiers_;
	};

}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_KEYBOARD_EVENT_HPP_