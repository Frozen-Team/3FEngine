#ifndef _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_EVENT_LISTENER_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_EVENT_LISTENER_HPP_

#include <event_system/events/f_events_enums.hpp>

namespace fengine
{
	class FEventListener
	{
	public:
		FEventListener() = default;

		virtual ~FEventListener() = default;

		bool IsListenableSource(fevents::EventSourceType type) const { return source_types_.IsSet(type); }

		const fevents::EventSourceTypes& source_types() const noexcept { return source_types_; }

	protected:
		void SetListenableSource(fevents::EventSourceType type) noexcept { this->source_types_.SetFlag(type); }

	private:
		fevents::EventSourceTypes source_types_;
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_LISTENERS_F_EVENT_LISTENER_HPP_