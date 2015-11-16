#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_WINDOW_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_WINDOW_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_window_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FWindowListener : virtual public FEventListener
	{
		friend class FEventsManager;
	public:
		FWindowListener() { SetListenableSource(fevents::kWindowSource); };

		virtual ~FWindowListener() = default;

	protected:
		virtual void OnWindowShown(FWindowEvent& e) {}

		virtual void OnWindowHidden(FWindowEvent& e) {}

		virtual void OnWindowExposed(FWindowEvent& e) {}

		virtual void OnWindowMoved(FWindowEvent& e) {}

		virtual void OnWindowResized(FWindowEvent& e) {}

		virtual void OnWindowSizeChanged(FWindowEvent& e) {}

		virtual void OnWindowMinimized(FWindowEvent& e) {}

		virtual void OnWindowMaximized(FWindowEvent& e) {}

		virtual void OnWindowRestored(FWindowEvent& e) {}

		virtual void OnWindowEnter(FWindowEvent& e) {}

		virtual void OnWindowLeave(FWindowEvent& e) {}

		virtual void OnWindowFocusGained(FWindowEvent& e) {}

		virtual void OnWindowFocusLost(FWindowEvent& e) {}

		virtual void OnWindowClose(FWindowEvent& e) {}

		virtual void CallEvent(FWindowEvent& e)
		{
			switch (e.type())
			{
			case fevents::kNoEvent: break;
			// TODO: Should we add?
			//case fevents::kSysWmEvent: break;
			case fevents::kWindowShown:
				OnWindowShown(e);
				break;
			case fevents::kWindowHidden:
				OnWindowHidden(e);
				break;
			case fevents::kWindowExposed:
				OnWindowExposed(e);
				break;
			case fevents::kWindowMoved:
				OnWindowMoved(e);
				break;
			case fevents::kWindowResized:
				OnWindowResized(e);
				break;
			case fevents::kWindowSizeChanged:
				OnWindowSizeChanged(e);
				break;
			case fevents::kWindowMinimized:
				OnWindowMinimized(e);
				break;
			case fevents::kWindowMaximized:
				OnWindowMaximized(e);
				break;
			case fevents::kWindowRestored:
				OnWindowRestored(e);
				break;
			case fevents::kWindowEnter:
				OnWindowEnter(e);
				break;
			case fevents::kWindowLeave:
				OnWindowLeave(e);
				break;
			case fevents::kWindowFocusGained:
				OnWindowFocusGained(e);
				break;
			case fevents::kWindowFocusLost:
				OnWindowFocusLost(e);
				break;
			case fevents::kWindowClose:
				OnWindowClose(e);
				break;
			default: break;
			}
		}
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_WINDOW_LISTENER_HPP_