#ifndef _3FENGINE_SRC_EVENTS_F_EVENT_HPP_
#define _3FENGINE_SRC_EVENTS_F_EVENT_HPP_

#include <events/f_events_enums.hpp>

namespace fengine
{
	class FEvent
	{
	public:

		explicit FEvent(fevents::EventType type) : accepted_(false) { this->type_ = type; }

		virtual ~FEvent() {}

		fevents::EventType type() const { return this->type_; }

		bool accepted() const { return this->accepted_; }

		void accept() { setAccepted(true); }

		void ignore() { setAccepted(false); }

		inline void setAccepted(bool accepted) { this->accepted_ = accepted; }

	private:
		fevents::EventType type_;
		bool accepted_;
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_EVENT_HPP_