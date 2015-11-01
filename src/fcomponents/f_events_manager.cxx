#include "f_events_manager.hpp"

#include <fcomponents/f_logger.hpp>

namespace fengine
{
	std::atomic_int FEventsManager::last_id_ = 0;

	int FEventsManager::RegisterEventHandler(FUnique<FKeyboardListener> handler)
	{
		LOG_IF(!handler, FATAL) << "Invalid pointer.";
		auto new_id = FEventsManager::GetNewEventId();
		keyboard_handlers_[new_id] = std::move(handler);
		return new_id;
	}

	int FEventsManager::RegisterEventHandler(FUnique<FMouseListener> handler)
	{
		LOG_IF(!handler, FATAL) << "Invalid pointer.";
		auto new_id = FEventsManager::GetNewEventId();
		mouse_handlers_[new_id] = std::move(handler);
		return new_id;
	}

	int FEventsManager::RegisterEventHandler(FUnique<FMouseWheelListener> handler)
	{
		LOG_IF(!handler, FATAL) << "Invalid pointer.";
		auto new_id = FEventsManager::GetNewEventId();
		mouse_wheel_handlers_[new_id] = std::move(handler);
		return new_id;
	}

	int FEventsManager::GetNewEventId()
	{
		if (last_id_ > kMaxLastId)
		{
			LOG(FATAL) << "Event ID limit exceeded!";
		}
		return last_id_++;
	}
}