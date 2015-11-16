#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_MOUSE_WHEEL_LISTENER_HPP_

#include <event_system/events/f_mouse_wheel_event.hpp>

namespace fengine
{
	class FMouseWheelListener : virtual public FEventListener
	{
		friend class FEventsManager;
	public:
		FMouseWheelListener() { SetListenableSource(fevents::kMouseWheelSource); }

		virtual ~FMouseWheelListener() = default;

	protected:
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