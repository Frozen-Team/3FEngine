#include "f_events_manager.hpp"

#include <fcomponents/f_logger.hpp>

#include <event_system/listeners/f_keyboard_listener.hpp>
#include <event_system/listeners/f_mouse_listener.hpp>
#include <event_system/listeners/f_mouse_wheel_listener.hpp>
#include <event_system/listeners/f_window_listener.hpp>
#include <event_system/listeners/f_joy_axis_motion_listener.hpp>
#include <event_system/listeners/f_joy_ball_motion_listener.hpp>
#include <event_system/listeners/f_joy_hat_motion_listener.hpp>
#include <event_system/listeners/f_joy_button_listener.hpp>
#include <event_system/listeners/f_joy_device_listener.hpp>

namespace fengine
{
	int FEventsManager::Deregister(int id)
	{
		const auto& it = handlers_.find(id);
		if (it != handlers_.cend())
		{
			handlers_.erase(it);
			return 0;
		}
		return -1;
	}

	void FEventsManager::HandleEvents()
	{
		while (PollEvent())
		{
			auto t = this->GetEventType();
			// TODO: Should we replace switch case to FMap. Perfomance issue?
			// TODO: Replace all fevents::k*Source with constexpr
			switch (t)
			{
			case fevents::kNoEvent: break;
			case fevents::kKeyPress:
			case fevents::kKeyRelease:
			{
				DelegateEvent<FKeyboardListener>(GetLastKeyboardEvent(), fevents::kKeyboardSource);
				break;
			}
			case fevents::kMouseMove:
			case fevents::kMouseButtonPress:
			case fevents::kMouseButtonRelease:
			{
				DelegateEvent<FMouseListener>(GetLastMouseEvent(), fevents::kMouseSource);
				break;
			}
			case fevents::kMouseWheel:
			{
				DelegateEvent<FMouseWheelListener>(GetLastMouseWheelEvent(), fevents::kMouseWheelSource);
				break;
			}
			case fevents::kJoyAxisMotion:
				DelegateEvent<FJoyAxisMotionListener>(GetLastJoyAxisMotionEvent(), fevents::kJoystickSource);
				break;
			case fevents::kJoyBallMotion:
				DelegateEvent<FJoyBallMotionListener>(GetLastJoyBallMotionEvent(), fevents::kJoystickSource);
				break;
			case fevents::kJoyHatMotion:
				DelegateEvent<FJoyHatMotionListener>(GetLastJoyHatMotionEvent(), fevents::kJoystickSource);
				break;
			case fevents::kJoyButtonPressed:
			case fevents::kJoyButtonReleased:
				DelegateEvent<FJoyButtonListener>(GetLastJoyButtonEvent(), fevents::kJoystickSource);
				break;
			case fevents::kJoyDeviceAdded:
			case fevents::kJoyDeviceRemoved:
				DelegateEvent<FJoyDeviceListener>(GetLastJoyDeviceEvent(), fevents::kJoystickSource);
				break;
			case fevents::kSysWmEvent:
			case fevents::kWindowShown:
			case fevents::kWindowHidden:
			case fevents::kWindowExposed:
			case fevents::kWindowMoved:
			case fevents::kWindowResized:
			case fevents::kWindowSizeChanged:
			case fevents::kWindowMinimized:
			case fevents::kWindowMaximized:
			case fevents::kWindowRestored:
			case fevents::kWindowEnter:
			case fevents::kWindowLeave:
			case fevents::kWindowFocusGained:
			case fevents::kWindowFocusLost:
			case fevents::kWindowClose:
			{
				DelegateEvent<FWindowListener>(GetLastWindowEvent(), fevents::kWindowSource);
				break;
			}
			default:
				LOG(WARNING) << "Unhandled event. Type: " << t;
				break;
			}
		}
	}

	int FEventsManager::GetNewEventId()
	{
		if (last_id_ > kMaxLastId)
		{
			LOG(FATAL) << "Event ID limit exceeded!";
			return -1;
		}
		return last_id_++;
	}
}
