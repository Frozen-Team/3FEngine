#ifndef _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_EVENT_HPP_
#define _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_EVENT_HPP_

#include <event_system/events/f_events_enums.hpp>

namespace fengine
{
	class FEvent
	{
	public:

		explicit FEvent(fevents::EventType type, unsigned which) : accepted_(false), which_(which){ this->type_ = type; }

		virtual ~FEvent() {}

		fevents::EventType type() const { return this->type_; }

		bool accepted() const { return this->accepted_; }

		void accept() { setAccepted(true); }

		void ignore() { setAccepted(false); }

		void setAccepted(bool accepted) { this->accepted_ = accepted; }

		unsigned which() const noexcept { return this->which_; }

	private:
		fevents::EventType type_;
		bool accepted_;
		unsigned which_;
	};
}
#endif // _3FENGINE_SRC_EVENT_SYSTEM_EVENTS_F_EVENT_HPP_