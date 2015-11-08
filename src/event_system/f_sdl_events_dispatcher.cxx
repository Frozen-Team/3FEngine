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
			if (event_.type == SDL_FINGERMOTION || event_.type == SDL_FINGERDOWN || event_.type == SDL_FINGERUP || event_.type == SDL_TEXTINPUT || event_.type == SDL_TEXTEDITING)
			{
				event_type_union_.sdl_type = 0;
			}
			else 
			{
				if (event_.type == SDL_WINDOWEVENT)
				{
					std::cout << "Which: " << event_.window.windowID << std::endl;
					event_type_union_.sdl_type = event_.type + event_.window.event + 1;
				} else
				{
					event_type_union_.sdl_type = event_.type;
				}
				
			}
			switch (event_.type)
			{
			case SDL_FIRSTEVENT: break;
			case SDL_QUIT: break;

			case SDL_APP_TERMINATING: break;
			case SDL_APP_LOWMEMORY: break;
			case SDL_APP_WILLENTERBACKGROUND:break;
			case SDL_APP_DIDENTERBACKGROUND:break;
			case SDL_APP_WILLENTERFOREGROUND:break;
			case SDL_APP_DIDENTERFOREGROUND:break;

			case SDL_WINDOWEVENT:break;
			case SDL_SYSWMEVENT:break;

			case SDL_KEYDOWN:break;
			case SDL_KEYUP:break;
			case SDL_TEXTEDITING:break;
			case SDL_TEXTINPUT:break;

			case SDL_MOUSEMOTION:break;
			case SDL_MOUSEBUTTONDOWN:break;
			case SDL_MOUSEBUTTONUP:break;

			case SDL_MOUSEWHEEL:break;

			case SDL_JOYAXISMOTION:break;

			case SDL_JOYBALLMOTION:break;

			case SDL_JOYHATMOTION:break;

			case SDL_JOYBUTTONDOWN:break;
			case SDL_JOYBUTTONUP:break;

			case SDL_JOYDEVICEADDED:break;
			case SDL_JOYDEVICEREMOVED:break;

			case SDL_CONTROLLERAXISMOTION:break;
			case SDL_CONTROLLERBUTTONDOWN:break;
			case SDL_CONTROLLERBUTTONUP:break;
			case SDL_CONTROLLERDEVICEADDED:break;
			case SDL_CONTROLLERDEVICEREMOVED:break;
			case SDL_CONTROLLERDEVICEREMAPPED:break;

			case SDL_FINGERDOWN:break;
			case SDL_FINGERUP:break;
			case SDL_FINGERMOTION:break;
			case SDL_DOLLARGESTURE:break;
			case SDL_DOLLARRECORD:break;
			case SDL_MULTIGESTURE:break;
			case SDL_CLIPBOARDUPDATE:break;
			case SDL_DROPFILE:break;
			case SDL_AUDIODEVICEADDED:break;
			case SDL_AUDIODEVICEREMOVED:break;
			case SDL_RENDER_TARGETS_RESET:break;
			case SDL_RENDER_DEVICE_RESET:break;
			default: break;
			}
			switch (event_.type)
			{
			case SDL_MOUSEWHEEL:
				mouse_wheel_delta_ = event_.wheel.direction;
				break;
			}
		}
		return ret;
	}
	fevents::KeyboardModifiers FSdlEventsDispatcher::GetKeyboardModifiers() const noexcept
	{
		return fevents::KeyboardModifiers(event_.key.keysym.mod);
	}
}