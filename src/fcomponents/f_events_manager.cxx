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
			case kNoEvent: break;
			case kKeyPress:
			case kKeyRelease:
			{
				FKeyboardEvent keyboard_event(t, this->GetKeyboardScanCode(), KeyboardModifiers(this->GetKeyboardModifiers()));
				for (auto& it = handlers_.begin(); it != handlers_.end() && !keyboard_event.accepted(); it++)
				{
					auto ptr = it->second.get();
					if (ptr->source_types().IsSet(kKeyboardSource))
					{
						static_cast<FKeyboardListener*>(it->second.get())->CallEvent(keyboard_event);
					}
				}
				break;
			}
			case kMouseMove:
			case kMouseButtonPress:
			case kMouseButtonRelease:
			{
				FMouseEvent mouse_event(t, this->GetMousePos(), this->GetMouseButton(), this->GetMouseButtons(), KeyboardModifiers(this->GetKeyboardModifiers()));
				for (auto& it = handlers_.begin(); it != handlers_.end() && !mouse_event.accepted(); it++)
				{
					auto ptr = it->second.get();
					if (ptr->source_types().IsSet(kMouseSource))
					{
						static_cast<FMouseListener*>(it->second.get())->CallEvent(mouse_event);
					}
				}
				break;
			}
			case kMouseWheel:
				//DelegateEvent(t, kMouseWheelSource);
				//break;
			case kJoyAxisMotion:
				//DelegateEvent(t, kJoystickSource);
				//break;

			default:
				LOG(WARNING) << "Unhandled event. Type: " << t;
				break;
			}
		}
	}

	//inline void FEventsManager::DelegateEvent(EventType type, EventSourceType source_type)
	//{
	//	switch (source_type)
	//	{
	//	case kNoSource:
	//		break;
	//	case kKeyboardSource:
	//		//Exec<FKeyboardListener>
	//		break;
	//	case kMouseSource:
	//		break;
	//	case kMouseWheelSource:
	//		break;
	//	case kJoystickSource:
	//		break;
	//	default:
	//		break;
	//	}
	//}

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