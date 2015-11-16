#include "f_gl_window.hpp"

namespace fengine
{
	FGlWindow::FGlWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags)
		: FWindow(title, pos, size, flags)
	{
		// TODO: Rewrite context
		SDL_Window* w = SDL_GetWindowFromID(GetSdlWindowId());
		context_ = SDL_GL_CreateContext(w);
		SDL_GL_MakeCurrent(w, context_);
	}
}