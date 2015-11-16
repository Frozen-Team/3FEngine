#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_LISTENER_HPP_

#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_mouse_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FMouseListener : virtual public FEventListener
	{
		friend class FEventsManager;
	public:
		FMouseListener() { SetListenableSource(fevents::kMouseSource); }

		virtual ~FMouseListener() = default;

	protected:
		virtual void OnMouseMove(FMouseEvent& e) {}

		virtual void OnMouseButtonPressed(FMouseEvent& e) {}

		virtual void OnMouseButtonReleased(FMouseEvent& e) {}

		virtual void CallEvent(FMouseEvent& e)
		{
			switch (e.type())
			{
			case fevents::kMouseMove:
				OnMouseMove(e);
				break;
			case fevents::kMouseButtonPress:
				OnMouseButtonPressed(e);
				break;
			case fevents::kMouseButtonRelease:
				OnMouseButtonReleased(e);
				break;
			default:
				break;
			}
		}
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_LISTENER_HPP_