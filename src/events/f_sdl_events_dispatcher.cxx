#include "f_sdl_events_dispatcher.hpp"

#include "SDL_joystick.h"
#include "SDL_mouse.h"
#include "SDL_keyboard.h"
#include "SDL_keycode.h"

namespace fengine
{
	bool FSdlEventsDispatcher::PollEvent()
	{
		auto ret = SDL_PollEvent(&this->event_) != 0;
		if (ret)
		{
			// Ignore some events
			if (event_.type == SDL_FINGERMOTION || event_.type == SDL_FINGERDOWN || event_.type == SDL_FINGERUP || event_.type == SDL_TEXTINPUT)
			{
				event_type_union_.sdl_type = 0;
			}
			else 
			{
				event_type_union_.sdl_type = event_.type;
			}
		}
		return ret;
	}
	KeyboardModifiers FSdlEventsDispatcher::GetKeyboardModifiers() const noexcept
	{
		return KeyboardModifiers(event_.key.keysym.mod);
	}
}