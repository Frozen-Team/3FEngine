#include "f_sdl_events_dispatcher.hpp"

void fengine::FSdlEventsDispather::PollEvents()
{
	while (SDL_PollEvent(&event_))
	{
		//SDL_GetMouseState()

	}
}
