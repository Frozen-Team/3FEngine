#ifndef _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_
#define _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_

#include "SDL_events.h"

#include <events/f_events_enums.hpp>

namespace fengine
{
	class FSdlEventsDispather
	{
	public:
		
	protected:
		inline bool PollEvent() noexcept;

		EventType inline type() const noexcept;

	private:
		SDL_Event event_;

		union EventTypeUnion
		{
			EventType ftype;
			unsigned int sdl_type;
		} event_type_union_;
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_