#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BUTTON_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BUTTON_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_button_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyButtonListener : public FEventListener
	{
	public:
		FJoyButtonListener() : FEventListener(fevents::EventSourceTypes(fevents::kJoystickSource)) {};

		virtual ~FJoyButtonListener() = default;

	protected:
		friend class FEventsManager;

		virtual void OnJoyButtonPressed(FJoyButtonEvent& e) {};

		virtual void OnJoyButtonReleased(FJoyButtonEvent& e) {};

		virtual void CallEvent(FJoyButtonEvent& e)
		{
			switch (e.type())
			{
			case fevents::kJoyButtonPressed:
				OnJoyButtonPressed(e);
				break;
			case fevents::kJoyButtonReleased:
				OnJoyButtonReleased(e);
				break;
			default:
				break;
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_BUTTON_LISTENER_HPP_