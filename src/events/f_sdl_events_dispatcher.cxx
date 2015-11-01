#include "f_sdl_events_dispatcher.hpp"

#include "SDL_joystick.h"
#include "SDL_mouse.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"

namespace fengine
{
	bool FSdlEventsDispather::PollEvent() noexcept
	{
		auto ret = SDL_PollEvent(&this->event_) != 0;
		if (ret)
		{
			event_type_union_.sdl_type = event_.type;
		}
		return ret;
	}
	inline EventType FSdlEventsDispather::type() const noexcept
	{
		return event_type_union_.ftype;
	}
}