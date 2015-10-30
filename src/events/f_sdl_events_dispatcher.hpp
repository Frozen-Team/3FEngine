#ifndef _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_
#define _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_

#include "SDL_events.h"
#include "SDL_joystick.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"

#include <utils/f_singleton.hpp>

namespace fengine {
	class FSdlEventsDispather : public futils::FSingleton<FSdlEventsDispather>
	{
	public:
		void PollEvents();

	private:
		SDL_Event event_;
	};
}
#endif // _3FENGINE_SRC_EVENTS_F_SDL_EVENTS_DISPATCHER_HPP_