#include "f_sdl_helper.hpp"

#include "SDL.h"
#include <fcomponents/f_logger.hpp>

#if defined SDL_JOYSTICK_DISABLED 
#error SDL compiled with no joystick support!
#endif
#if defined SDL_HAPTIC_DISABLED
#error SDL compiled with no haptic device support!
#endif

namespace fengine
{
	FString FSdlHelper::last_error_ = "";

	FSdlHelper::FSdlHelper()
	{
		LOG(INFO) << "FSdlHelper ctor";
	}

	FSdlHelper::~FSdlHelper()
	{
		LOG(INFO) << "FSdlHelper dtor";
		SDL_Quit();
	}

	bool FSdlHelper::CheckError() noexcept
	{
		auto error_str = SDL_GetError();
		if ((error_str != nullptr) & (last_error_.assign(error_str).length() != 0))
		{
			last_error_.assign(error_str);
			SDL_ClearError();
			return true;
		}
		return false;
	}

	const FString& FSdlHelper::GetLastError() noexcept
	{
		return last_error_;
	}

	int FSdlHelper::Initialize()
	{
		LOG_IF(!SDL_SetHint(SDL_HINT_ACCELEROMETER_AS_JOYSTICK, "0"), FATAL) << "SetHint failed";
		auto ret_code = SDL_Init(SDL_INIT_EVENTS | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC | SDL_INIT_JOYSTICK | SDL_INIT_TIMER | SDL_INIT_VIDEO);
		if (ret_code < 0)
		{
			return ret_code;
		}
		LOG(INFO) << "Initialize SDL: Success.";
		return 0;
	}
}
