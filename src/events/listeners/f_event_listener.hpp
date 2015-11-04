#ifndef _3FENGINE_SRC_EVENTS_LISTENERS_F_EVENT_LISTENER_HPP_
#define _3FENGINE_SRC_EVENTS_LISTENERS_F_EVENT_LISTENER_HPP_

#include <events/f_events_enums.hpp>

namespace fengine
{
	class FEventListener
	{
	public:
		virtual ~FEventListener() = default;

		explicit FEventListener(EventSourceTypes types) { this->source_types_ |= types; }

		const EventSourceTypes& source_types() const noexcept { return source_types_; }

	private:
		EventSourceTypes source_types_;
	};
}
#endif // _3FENGINE_SRC_EVENTS_LISTENERS_F_EVENT_LISTENER_HPP_