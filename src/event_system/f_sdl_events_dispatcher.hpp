#ifndef _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_

#include "SDL_events.h"

#include <utils/f_typedefs.hpp>
#include <event_system/events/f_events_enums.hpp>

namespace fengine
{
	class FSdlEventsDispatcher
	{
	public:
		FSdlEventsDispatcher();
		~FSdlEventsDispatcher();
		
	protected:

		bool PollEvent();

		fevents::EventType GetEventType() const noexcept { return event_type_union_.type; }
		// TODO: Fix unsafe direct conversion.
		fevents::KeyboardKey GetKeyboardScanCode() const { return static_cast<fevents::KeyboardKey>(event_.key.keysym.scancode); }

		int GetKeyboardSymbol() const { return event_.key.keysym.sym; }

		fevents::KeyboardModifiers GetKeyboardModifiers() const noexcept;

		FPoint2i GetMousePos() const { return FPoint2i(event_.motion.x, event_.motion.y); }

		fevents::MouseButton GetMouseButton() const { return fevents::MouseButton(event_.button.button); }

		fevents::MouseButtons GetMouseButtons() const { return fevents::MouseButtons(event_.motion.state); }

		int GetMouseWheelDelta() const noexcept { return mouse_wheel_delta_; }

	private:
		static int JoystickDeviceEventsHandler(void* data, SDL_Event* event);

		static void OpenJoystick(unsigned which);

		static void CloseJoystick(unsigned which);

		static FString GetJoystickGuid(unsigned which);

	private:
		static FMap<unsigned, SDL_Joystick*> joystick_handles_;

		int mouse_wheel_delta_;
		FPoint2i mouse_pos_;
		SDL_Event event_;

		union EventTypeUnion
		{
			fevents::EventType type;
			unsigned int sdl_type;
		} event_type_union_;
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_