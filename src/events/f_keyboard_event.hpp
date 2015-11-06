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
		explicit FKeyboardEvent(fevents::EventType type, fevents::KeyboardKey key, fevents::KeyboardModifiers modifiers);

		virtual ~FKeyboardEvent() {}

		fevents::KeyboardKey key() const noexcept { return this->key_; }

		const fevents::KeyboardModifiers& modifiers() const noexcept { return this->modifiers_; }

	private:
		fevents::KeyboardKey key_;
		fevents::KeyboardModifiers modifiers_;
	};

}
#endif // _3FENGINE_SRC_F_KEYBOARD_EVENT_HPP_