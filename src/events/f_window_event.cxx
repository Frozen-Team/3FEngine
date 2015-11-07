#include "f_window_event.hpp"
#include <fcomponents/f_logger.hpp>

namespace fengine
{

	FWindowEvent::FWindowEvent(fevents::EventType type, const FPoint2i& pos, const FPoint2i& size)
		: FEvent(type), pos_(pos), size_(size)
	{
		// TODO: Add kSysWmEvent?
		LOG_IF(type < fevents::kWindowShown || type > fevents::kWindowClose, FATAL) << "Invalid window event type: " << type;
	}
}
