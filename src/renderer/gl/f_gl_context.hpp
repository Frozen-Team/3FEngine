#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_CONTEXT_HPP
#define _3FENGINE_SRC_RENDERER_GL_F_GL_CONTEXT_HPP

#include <SDL.h>
#include <renderer/gl/f_gl_include.hpp>
#include <utils/f_typedefs.hpp>

namespace fengine
{
	class FGlContext
	{
		F_DISABLE_COPY(FGlContext)
	public:
		explicit FGlContext() = default;

	private:
		SDL_GLContext gl_context_;
		
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_CONTEXT_HPP