#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_WINDOW_HPP
#define _3FENGINE_SRC_RENDERER_GL_F_GL_WINDOW_HPP

#include <gui/f_window.hpp>

namespace fengine
{
	class FGlWindow : public FWindow
	{
	public:
		FGlWindow() = default;
		
		explicit FGlWindow(const FString& title, const FPoint2i& pos, const FPoint2i& size, const fgui::WindowFlags& flags);

		virtual ~FGlWindow() = default;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_WINDOW_HPP