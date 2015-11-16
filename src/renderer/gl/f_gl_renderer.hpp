#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_

#include <renderer/f_renderer_interface.hpp>
#include "f_gl_window.hpp"

namespace fengine
{
	class FGlRenderer : public FRendererInterface
	{
	public:
		
		FGlRenderer();
		virtual ~FGlRenderer() override;
		
		virtual void RenderFrame(float delta) override;

		virtual const FWindow& GetActiveWindow() override { return *window_; }

	private:
		void CreateWindowWithContext();

	private:
		FShared<FGlWindow> window_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_