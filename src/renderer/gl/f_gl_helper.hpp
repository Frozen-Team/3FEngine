#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_HELPER_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_HELPER_HPP_

#include <renderer/gl/f_gl_include.hpp>

#include "utils/f_typedefs.hpp"
#include "utils/f_singleton.hpp"

namespace fengine {
	// Helper must be constructed right after context creation.
	class FGlHelper : public futils::FSingleton<FGlHelper>
	{

	public:
		enum class GlExtension
		{
			kGlExtFramebufferBlit,
		};
	public:
		FGlHelper();

		virtual ~FGlHelper();
		
		static bool IsExtensionSupported(const FString& ext_name);

		static bool IsExtensionSupported(GlExtension ext);

		static bool CheckErrors();

		static const FString& GetLastErrors() { return last_errors_; }

		static FString GetErrorsDescription();

	private:
		static FString GetGlErrorDescription(GLenum err);

	private:
		static const FMap<GlExtension, FString> ext_names_;
		static FVector<FString> exts_supported_;
		static FString gl_vendor_;
		static FString gl_renderer_;
		static FString gl_ver_;
		static FString gl_shading_lang_ver_;
		static int major_;
		static int minor_;
		static bool was_error_;
		static FString last_errors_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_HELPER_HPP_