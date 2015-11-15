#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_

#include <renderer/f_renderer_interface.hpp>

namespace fengine
{
	class FGlRenderer : public FRendererInterface
	{
	public:
		FGlRenderer();
		virtual ~FGlRenderer() override;
		
		virtual void RenderFrame(float delta) override;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_