#ifndef _3FENGINE_SRC_EVENTS_F_KEYBOARD_LISTENER_HPP_
#define _3FENGINE_SRC_EVENTS_F_KEYBOARD_LISTENER_HPP_

#include <utils/f_typedefs.hpp>
#include <events/f_keyboard_event.hpp>

namespace fengine
{
	class FKeyboardListener
	{
	public:
		FKeyboardListener() = default;

		virtual ~FKeyboardListener() = default;

	protected:
		virtual void OnKeyPressed(const FKeyboardEvent& e) {};

		virtual void OnKeyReleased(const FKeyboardEvent& e) {};
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_KEYBOARD_LISTENER_HPP_