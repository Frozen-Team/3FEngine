#ifndef _3FENGINE_SRC_RENDERER_GL_HPP_
#define _3FENGINE_SRC_RENDERER_GL_HPP_

#include "SDL.h"
#include "SDL_opengl.h"

#include "utils/f_typedefs.hpp"
#include "utils/f_singleton.hpp"

namespace fengine {

	class GlHelper : public futils::FSingleton<GlHelper>
	{
	public:
		GlHelper();
		typedef enum
		{
			kGlExtFramebufferBlit,

		} GlExtension;

	private:
		const static FMap<GlExtension, FString> extension_names_;
		//static FMap<FString, 
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_HPP_