#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_HELPER_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_HELPER_HPP_

#include "GL\glew.h"
#include "SDL.h"
#include "SDL_opengl.h"

#include "utils/f_typedefs.hpp"
#include "utils/f_singleton.hpp"

namespace fengine {
	// Helper must be constructed right after context creation.
	class GlHelper : public futils::FSingleton<GlHelper>
	{
	public:
		typedef enum
		{
			kGlExtFramebufferBlit,
		} GlExtension;
	public:
		GlHelper();
		
		static bool IsExtensionSupported(const FString& ext_name);

		static bool IsExtensionSupported(GlExtension ext);

	private:
		static const FMap<GlExtension, FString> ext_names_;
		static FVector<FString> exts_supported_;
		static FString gl_vendor_;
		static FString gl_renderer_;
		static FString gl_ver_;
		static FString gl_shading_lang_ver_;
		int major_;
		int minor_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_HELPER_HPP_