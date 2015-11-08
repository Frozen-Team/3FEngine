#include "f_sdl_helper.hpp"

#include "SDL.h"

namespace fengine
{
	FString FSdlHelper::last_error_ = "";

	bool FSdlHelper::CheckError() noexcept
	{
		auto error_str = SDL_GetError();
		if (error_str != nullptr)
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
}
