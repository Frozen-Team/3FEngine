#ifndef _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_LISTENER_HPP_
#define _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_LISTENER_HPP_

#include <utils/f_typedefs.hpp>
#include <events/listeners/f_event_listener.hpp>
#include <events/f_mouse_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FMouseListener : public FEventListener
	{
	public:
		FMouseListener() : FEventListener(kMouseSource) {}

		virtual ~FMouseListener() = default;

	private:
		int k;

	protected:
		friend class FEventsManager;

		virtual void OnMouseMove(FMouseEvent& e) {}

		virtual void OnMouseButtonPressed(FMouseEvent& e) {}

		virtual void OnMouseButtonReleased(FMouseEvent& e) {}

	private:
		inline void CallEvent(FMouseEvent& e)
		{
			switch (e.type())
			{
			case kMouseMove:
				OnMouseMove(e);
				break;
			case kMouseButtonPress:
				OnMouseButtonPressed(e);
				break;
			case kMouseButtonRelease:
				OnMouseButtonReleased(e);
				break;
			default:
				break;
			}
		}
	};
}

#endif // _3FENGINE_SRC_EVENTS_LISTENERS_F_MOUSE_LISTENER_HPP_