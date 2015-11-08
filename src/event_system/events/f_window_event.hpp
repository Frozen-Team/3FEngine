#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_WINDOW_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_WINDOW_EVENT_HPP_

#include "f_event.hpp"

namespace fengine
{
	class FWindowEvent : public FEvent
	{
	public:
		explicit FWindowEvent(fevents::EventType type, unsigned which, const FPoint2i& pos, const FPoint2i& size);

		const FPoint2i& pos() const noexcept { return this->pos_; }

		const FPoint2i& size() const noexcept { return this->size_; }

	private:
		FPoint2i pos_;
		FPoint2i size_;
	};
}

#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_WINDOW_EVENT_HPP_