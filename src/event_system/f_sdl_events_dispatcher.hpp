#ifndef _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_

#include "SDL_events.h"

#include <utils/f_typedefs.hpp>
#include <event_system/events/f_events_enums.hpp>
#include <event_system/events/f_joy_axis_motion_event.hpp>
#include <event_system/events/f_joy_ball_motion_event.hpp>
#include <event_system/events/f_joy_button_event.hpp>
#include <event_system/events/f_joy_device_event.hpp>
#include <event_system/events/f_joy_hat_motion_event.hpp>
#include <event_system/events/f_keyboard_event.hpp>
#include <event_system/events/f_mouse_event.hpp>
#include <event_system/events/f_mouse_wheel_event.hpp>
#include <event_system/events/f_window_event.hpp>

namespace fengine
{
	class FSdlEventsDispatcher
	{
		F_DISABLE_COPY(FSdlEventsDispatcher)
	public:
		FSdlEventsDispatcher();
		virtual ~FSdlEventsDispatcher();
		
	protected:

		bool PollEvent();


		fevents::EventType GetEventType() const noexcept { return last_event_.type; }
		// TODO: Fix unsafe direct conversion.
		fevents::KeyboardKey GetKeyboardScanCode() const { return static_cast<fevents::KeyboardKey>(event_.key.keysym.scancode); }

		int GetKeyboardSymbol() const { return event_.key.keysym.sym; }

		fevents::KeyboardModifiers GetKeyboardModifiers() const noexcept;

		FPoint2i GetMousePos() const { return FPoint2i(event_.motion.x, event_.motion.y); }

		fevents::MouseButton GetMouseButton() const { return fevents::MouseButton(event_.button.button); }

		fevents::MouseButtons GetMouseButtons() const { return fevents::MouseButtons(event_.motion.state); }

		int GetMouseWheelDelta() const noexcept { return mouse_wheel_delta_; }

		FJoyAxisMotionEvent GetLastJoyAxisMotionEvent() const noexcept { return FJoyAxisMotionEvent(jame_.which, jame_.axis, jame_.value); }

		FJoyBallMotionEvent GetLastJoyBallMotionEvent() const noexcept { return FJoyBallMotionEvent(jbme_.which, jbme_.ball, jbme_.delta); }

		FJoyButtonEvent GetLastJoyButtonEvent() const noexcept { return FJoyButtonEvent(jbe_.type, jbe_.which, jbe_.button); }

		FJoyDeviceEvent GetLastJoyDeviceEvent() const noexcept { return FJoyDeviceEvent(jde_.type, jde_.which); }

		FJoyHatMotionEvent GetLastJoyHatMotionEvent() const noexcept { return FJoyHatMotionEvent(jhme_.which, jhme_.hat, jhme_.value); }

		FKeyboardEvent GetLastKeyboardEvent() const noexcept { return FKeyboardEvent(ke_.type, ke_.which, ke_.key, ke_.modifiers); }
		
		FMouseEvent GetLastMouseEvent() const noexcept { return FMouseEvent(me_.type, me_.which, me_.pos, me_.button, me_.buttons, me_.modifiers); }

		FMouseWheelEvent GetLastMouseWheelEvent() const noexcept { return FMouseWheelEvent(mwe_.delta, mwe_.which, mwe_.pos, mwe_.buttons, mwe_.modifiers); }

		FWindowEvent GetLastWindowEvent() const noexcept { return FWindowEvent(we_.type, we_.which, we_.pos, we_.size); }

	private:
		static int JoystickDeviceEventsHandler(void* data, SDL_Event* event);

		static int UnusedEventsFilter(void* data, SDL_Event* event);

		static void OpenJoystick(unsigned which);

		static void CloseJoystick(unsigned which);

		static FString GetJoystickGuid(unsigned which);
		
		struct
		{
			unsigned which;
			unsigned axis;
			int value;
		} jame_; // LastJoyAxisMotionEvent

		struct
		{
			unsigned which;
			unsigned ball;
			FPoint2i delta;
		} jbme_; // LastJoyBallMotionEvent	

		struct
		{
			fevents::EventType type;
			unsigned which;
			unsigned button;
		} jbe_; // LastJoyButtonEvent

		struct
		{
			fevents::EventType type;
			unsigned which;
		} jde_; // LastJoyDeviceEvent

		struct
		{
			unsigned which;
			unsigned hat;
			int value;
		} jhme_; // LastJoyHatMotionEvent

		struct
		{
			fevents::EventType type;
			unsigned which;
			fevents::KeyboardKey key;
			fevents::KeyboardModifiers modifiers;
		} ke_; // LastKeyboardEvent

		struct
		{
			fevents::EventType type;
			unsigned which;
			FPoint2i pos;
			fevents::MouseButton button;
			fevents::MouseButtons buttons;
			fevents::KeyboardModifiers modifiers;
		} me_; // LastMouseEvent

		struct
		{
			FPoint2i delta;
			unsigned which;
			FPoint2i pos;
			fevents::MouseButtons buttons;
			fevents::KeyboardModifiers modifiers;
		} mwe_; // LastMouseWheelEvent

		struct
		{
			fevents::EventType type;
			unsigned which;
			FPoint2i pos;
			FPoint2i size;
		} we_; // LastWindowEvent

		static FMap<unsigned, SDL_Joystick*> joystick_handles_;

		int mouse_wheel_delta_;
		FPoint2i mouse_pos_;
		SDL_Event event_;

		union EventTypeUnion
		{
			fevents::EventType type;
			unsigned int sdl_type;
			EventTypeUnion(): type(fevents::EventType::kNoEvent) { static_assert(sizeof(type) == sizeof(sdl_type), "SDL event type and EventType must have same size."); }
		} last_event_;
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_