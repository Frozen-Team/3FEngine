#ifndef _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_
#define _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_

#include "SDL_events.h"

#include <utils/f_typedefs.hpp>
#include <events/f_events_enums.hpp>

namespace fengine
{
	class FSdlEventsDispatcher
	{
	public:
		
	protected:

		bool PollEvent();

		EventType inline GetEventType() const noexcept { return event_type_union_.type; }
		// Unsafe direct conversion.
		KeyboardKey inline GetKeyboardScanCode() const { return static_cast<KeyboardKey>(event_.key.keysym.scancode); }

		int inline GetKeyboardSymbol() const { return event_.key.keysym.sym; }

		KeyboardModifiers GetKeyboardModifiers() const noexcept;

		FPoint2i GetMousePos() { return FPoint2i(event_.motion.x, event_.motion.y); }

		MouseButton GetMouseButton() { return MouseButton(event_.button.button); }

		MouseButtons GetMouseButtons() { return MouseButtons(event_.motion.state); }

	private:
		FPoint2i mouse_pos_;
		SDL_Event event_;

		union EventTypeUnion
		{
			EventType type;
			unsigned int sdl_type;
		} event_type_union_;
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_