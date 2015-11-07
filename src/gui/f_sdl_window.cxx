#include "f_sdl_window.hpp"
#include <helpers/f_sdl_helper.hpp>


namespace fengine
{
	FSdlWindow::FSdlWindow()
		: window_(nullptr)
	{
	}

	unsigned FSdlWindow::GetSdlWindowId() const noexcept
	{
		return SDL_GetWindowID(window_);
	}

	fgui::WindowFlags FSdlWindow::GetSdlWindowFlags() const noexcept
	{
		return fgui::WindowFlags(SDL_GetWindowFlags(window_));
	}

	unsigned FSdlWindow::CreateSdlWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags)
	{
		if (window_ != nullptr)
		{
			return GetSdlWindowId();
		}

		window_ = SDL_CreateWindow(title.c_str(), pos.x(), pos.y(), size.x(), size.y(), flags.ToNumber());
		LOG_IF((window_ == nullptr) | (FSdlHelper::CheckError()), FATAL) << "Cannot create window. SDL error: " << FSdlHelper::GetLastError();

		return GetSdlWindowId();
	}
}
