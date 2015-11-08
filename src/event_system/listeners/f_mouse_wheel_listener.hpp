#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_

#include <event_system/events/f_mouse_wheel_event.hpp>

namespace fengine
{
	class FMouseWheelListener : public FEventListener
	{
	public:
		FMouseWheelListener() : FEventListener(fevents::EventSourceTypes(fevents::kMouseSource)) {}

		virtual ~FMouseWheelListener() = default;

	protected:
		friend class FEventsManager;

		virtual void OnMouseWheelScrolled(FMouseWheelEvent& e) {}

		virtual void CallEvent(FMouseWheelEvent& e)
		{
			if (e.type() == fevents::kMouseWheel)
			{
				OnMouseWheelScrolled(e);
			}
		}
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_