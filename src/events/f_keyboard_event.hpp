#ifndef _3FENGINE_SRC_F_KEYBOARD_EVENT_HPP_
#define _3FENGINE_SRC_F_KEYBOARD_EVENT_HPP_

#include <fcomponents/f_logger.hpp>
#include <events/f_event.hpp>
#include <utils/f_flags.hpp>
#include <events/f_events_enums.hpp>

namespace fengine 
{
	class FKeyboardEvent : public FEvent
	{
	public:
		explicit FKeyboardEvent(EventType type, KeyboardKey key, KeyboardModifiers modifiers);

		virtual ~FKeyboardEvent() {}

		KeyboardKey key() const noexcept { return this->key_; }

		const KeyboardModifiers& modifiers() const noexcept { return this->modifiers_; }

	private:
		KeyboardKey key_;
		KeyboardModifiers modifiers_;
	};

}
#endif // _3FENGINE_SRC_F_KEYBOARD_EVENT_HPP_