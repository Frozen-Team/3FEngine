#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_DEVICE_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_DEVICE_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>
#include <event_system/listeners/f_event_listener.hpp>
#include <event_system/events/f_joy_device_event.hpp>

#include <fcomponents/f_events_manager.hpp>

namespace fengine
{
	class FJoyDeviceListener : public FEventListener
	{
	public:
		FJoyDeviceListener() : FEventListener(fevents::EventSourceTypes(fevents::kJoystickSource)) {};

		virtual ~FJoyDeviceListener() = default;

	protected:
		friend class FEventsManager;

		virtual void OnJoyDeviceAdded(FJoyDeviceEvent& e) {};

		virtual void OnJoyDeviceRemoved(FJoyDeviceEvent& e) {};

		virtual void CallEvent(FJoyDeviceEvent& e)
		{
			switch (e.type())
			{
			case fevents::kJoyDeviceAdded:
				OnJoyDeviceAdded(e);
				break;
			case fevents::kJoyDeviceRemoved:
				OnJoyDeviceRemoved(e);
				break;
			default:
				break;
			}
		}
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_JOY_DEVICE_LISTENER_HPP_