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

		static bool PollEvent();


		static fevents::EventType GetEventType() noexcept { return last_event_.type; }
		//// TODO: Fix unsafe direct conversion.
		//fevents::KeyboardKey GetKeyboardScanCode() const { return static_cast<fevents::KeyboardKey>(event_.key.keysym.scancode); }

		//int GetKeyboardSymbol() const { return event_.key.keysym.sym; }

		static fevents::KeyboardModifiers GetKeyboardModifiers() noexcept;

		//FPoint2i GetMousePos() const { return FPoint2i(event_.motion.x, event_.motion.y); }

		//fevents::MouseButton GetMouseButton() const { return fevents::MouseButton(event_.button.button); }

		//fevents::MouseButtons GetMouseButtons() const { return fevents::MouseButtons(event_.motion.state); }

		//int GetMouseWheelDelta() const noexcept { return mouse_wheel_delta_; }

		static FJoyAxisMotionEvent GetLastJoyAxisMotionEvent() noexcept { return FJoyAxisMotionEvent(jame_.which, jame_.axis, jame_.value); }

		static FJoyBallMotionEvent GetLastJoyBallMotionEvent() noexcept { return FJoyBallMotionEvent(jbme_.which, jbme_.ball, jbme_.delta); }

		static FJoyButtonEvent GetLastJoyButtonEvent() noexcept { return FJoyButtonEvent(jbe_.type, jbe_.which, jbe_.button); }

		static FJoyDeviceEvent GetLastJoyDeviceEvent() noexcept { return FJoyDeviceEvent(jde_.type, jde_.which); }

		static FJoyHatMotionEvent GetLastJoyHatMotionEvent() noexcept { return FJoyHatMotionEvent(jhme_.which, jhme_.hat, jhme_.value); }

		static FKeyboardEvent GetLastKeyboardEvent() noexcept { return FKeyboardEvent(ke_.type, ke_.which, ke_.key, ke_.modifiers); }
		
		static FMouseEvent GetLastMouseEvent() noexcept { return FMouseEvent(me_.type, me_.which, me_.pos, me_.button, me_.buttons, me_.modifiers); }

		static FMouseWheelEvent GetLastMouseWheelEvent() noexcept { return FMouseWheelEvent(mwe_.delta, mwe_.which, mwe_.pos, mwe_.buttons, mwe_.modifiers); }

		static FWindowEvent GetLastWindowEvent() noexcept { return FWindowEvent(we_.type, we_.which, we_.pos, we_.size); }

	private:
		static int JoystickDeviceEventsHandler(void* data, SDL_Event* event);

		static int UnusedEventsFilter(void* data, SDL_Event* event);

		static void OpenJoystick(unsigned which);

		static void CloseJoystick(unsigned which);

		static FString GetJoystickGuid(unsigned which);
		
		static struct
		{
			unsigned which;
			unsigned axis;
			int value;
		} jame_; // LastJoyAxisMotionEvent

		static struct jbme_internal_
		{
			unsigned which;
			unsigned ball;
			FPoint2i delta;
		} jbme_; // LastJoyBallMotionEvent	

		static struct jbe_internal_
		{
			fevents::EventType type;
			unsigned which;
			unsigned button;
		} jbe_; // LastJoyButtonEvent

		static struct jde_internal_
		{
			fevents::EventType type;
			unsigned which;
		} jde_; // LastJoyDeviceEvent

		static struct jhme_internal_
		{
			unsigned which;
			unsigned hat;
			int value;
		} jhme_; // LastJoyHatMotionEvent

		static struct ke_internal_
		{
			fevents::EventType type;
			unsigned which;
			fevents::KeyboardKey key;
			fevents::KeyboardModifiers modifiers;
		} ke_; // LastKeyboardEvent

		static struct me_internal_
		{
			fevents::EventType type;
			unsigned which;
			FPoint2i pos;
			fevents::MouseButton button;
			fevents::MouseButtons buttons;
			fevents::KeyboardModifiers modifiers;
		} me_; // LastMouseEvent

		static struct mwe_internal_
		{
			FPoint2i delta;
			unsigned which;
			FPoint2i pos;
			fevents::MouseButtons buttons;
			fevents::KeyboardModifiers modifiers;
		} mwe_; // LastMouseWheelEvent

		static struct we_internal_
		{
			fevents::EventType type;
			unsigned which;
			FPoint2i pos;
			FPoint2i size;
		} we_; // LastWindowEvent

		static FMap<unsigned, SDL_Joystick*> joystick_handles_;

		static SDL_Event event_;

		static union EventTypeUnion
		{
			fevents::EventType type;
			unsigned int sdl_type;
			EventTypeUnion(): type(fevents::EventType::kNoEvent) { static_assert(sizeof(type) == sizeof(sdl_type), "SDL event type and EventType must have same size."); }
		} last_event_;
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_F_SDL_EVENTS_DISPATCHER_HPP_