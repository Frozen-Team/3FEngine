#include "f_events_manager.hpp"

#include <fcomponents/f_logger.hpp>

#include <events/listeners/f_keyboard_listener.hpp>
#include <events/listeners/f_mouse_listener.hpp>
#include <events/listeners/f_mouse_wheel_listener.hpp>

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

			switch (t)
			{
			case fevents::kNoEvent: break;
			case fevents::kKeyPress:
			case fevents::kKeyRelease:
			{
				FKeyboardEvent keyboard_event(t, this->GetKeyboardScanCode(), fevents::KeyboardModifiers(this->GetKeyboardModifiers()));
				DelegateEvent<FKeyboardListener>(keyboard_event, fevents::kKeyboardSource);
				break;
			}
			case fevents::kMouseMove:
			case fevents::kMouseButtonPress:
			case fevents::kMouseButtonRelease:
			{
				FMouseEvent mouse_event(t, this->GetMousePos(), this->GetMouseButton(), this->GetMouseButtons(), fevents::KeyboardModifiers(this->GetKeyboardModifiers()));
				DelegateEvent<FMouseListener>(mouse_event, fevents::kMouseSource);
				break;
			}
			case fevents::kMouseWheel:
				//DelegateEvent(t, kMouseWheelSource);
				//break;
			case fevents::kJoyAxisMotion:
				//DelegateEvent(t, kJoystickSource);
				break;

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