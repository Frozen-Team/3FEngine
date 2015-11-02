#include "f_events_manager.hpp"

#include <fcomponents/f_logger.hpp>

#include <events/listeners/f_keyboard_listener.hpp>
#include <events/listeners/f_mouse_listener.hpp>
#include <events/listeners/f_mouse_wheel_listener.hpp>

namespace fengine
{
	int FEventsManager::Register(FUnique<FEventListener> handler)
	{
		LOG_IF(!handler, FATAL) << "Invalid pointer.";
		auto new_id = FEventsManager::GetNewEventId();
		handlers_[new_id] = std::move(handler);
		return new_id;
	}

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
			{
				FKeyboardEvent keyboardEvent(t, this->GetKeyboardScanCode(), KeyboardModifiers(this->GetKeyboardModifiers()));
				for (auto& it = handlers_.begin(); it != handlers_.end() && !keyboardEvent.accepted(); it++)
				{
					auto ptr = it->second.get();
					if (ptr->source_types().IsSet(kKeyboardSource))
					{
						static_cast<FKeyboardListener*>(it->second.get())->OnKeyPressed(keyboardEvent);
					}
				}
				break;
			}
			case kKeyRelease:
			{
				FKeyboardEvent keyboardEvent(t, this->GetKeyboardScanCode(), KeyboardModifiers(this->GetKeyboardModifiers()));
				for (auto& it = handlers_.begin(); it != handlers_.end() && !keyboardEvent.accepted(); it++)
				{
					auto ptr = it->second.get();
					if (ptr->source_types().IsSet(kKeyboardSource))
					{
						static_cast<FKeyboardListener*>(it->second.get())->OnKeyReleased(keyboardEvent);
					}
				}
				break;
			}
			case kMouseMove:
			case kMouseButtonPress:
			case kMouseButtonRelease:
				//DelegateEvent(t, kMouseSource);
				//break;
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