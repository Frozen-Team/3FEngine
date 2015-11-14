#include "f_gl_window.hpp"

namespace fengine
{
	FGlWindow::FGlWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags)
		: FWindow(title, pos, size, flags)
	{}
}