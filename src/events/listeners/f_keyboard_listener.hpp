#ifndef _3FENGINE_SRC_EVENTS_F_KEYBOARD_LISTENER_HPP_
#define _3FENGINE_SRC_EVENTS_F_KEYBOARD_LISTENER_HPP_

#include <events/f_events_enums.hpp>
#include <events/listeners/f_event_listener.hpp>
#include <events/f_keyboard_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FKeyboardListener : public FEventListener
	{
	public:
		FKeyboardListener() : FEventListener(fevents::EventSourceTypes(fevents::kKeyboardSource)) {};

		virtual ~FKeyboardListener() = default;

	protected:
		friend class FEventsManager;
		
		virtual void OnKeyPressed(FKeyboardEvent& e) {};

		virtual void OnKeyReleased(FKeyboardEvent& e) {};
	private:
		void CallEvent(FKeyboardEvent& e)
		{
			switch (e.type())
			{
			case fevents::kKeyPress:
				OnKeyPressed(e);
				break;
			case fevents::kKeyRelease:
				OnKeyReleased(e);
				break;
			default:
				break;
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_KEYBOARD_LISTENER_HPP_