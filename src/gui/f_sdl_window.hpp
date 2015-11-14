#ifndef _3FENGINE_SRC_GUI_F_SDL_WINDOW_HPP_
#define _3FENGINE_SRC_GUI_F_SDL_WINDOW_HPP_

#include <SDL.h>

#include <utils/f_typedefs.hpp>
#include <gui/f_gui_enums.hpp>

namespace fengine
{
	class FSdlWindow
	{
		F_DISABLE_COPY(FSdlWindow)
	public:
		FSdlWindow();

	protected:
		unsigned CreateSdlWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags);

		unsigned GetSdlWindowId() const noexcept;

		fgui::WindowFlags GetSdlWindowFlags() const noexcept;

	private:
		SDL_Window* window_;
	};
}

#endif // _3FENGINE_SRC_GUI_F_SDL_WINDOW_HPP_