#include "f_gl_helper.hpp"
#include <utils/f_utils.hpp>
#include <fcomponents/f_logger.hpp>

namespace fengine {
	// Map contains all names of extensions from GlExtension enum.
	const FMap<FGlHelper::GlExtension, FString> FGlHelper::ext_names_ = 
	{
		{ GlExtension::kGlExtFramebufferBlit, futils::ToLower("GL_EXT_Framebuffer_blit") }
	};
	FVector<FString> FGlHelper::exts_supported_;
	FString FGlHelper::last_errors_;
	FString FGlHelper::gl_vendor_;
	FString FGlHelper::gl_renderer_;
	int FGlHelper::major_ = 0;
	int FGlHelper::minor_ = 0;
	FString FGlHelper::gl_ver_;
	FString FGlHelper::gl_shading_lang_ver_;
	bool FGlHelper::was_error_ = false;

	FGlHelper::FGlHelper()
	{
		LOG(INFO) << "FGlHelper ctor";
		glewExperimental = GL_TRUE;
		auto err = GLEW_OK;
		// TODO: glew uses deprecated gl call glGetString(GL_EXTENSIONS). Update to newer version.
		LOG_IF((err = glewInit()) != GLEW_OK, FATAL) << "GLEW initialization error: " << glewGetErrorString(err);
		// ... workaround for now
		auto swallow_err = glGetError();

		last_errors_.reserve(256);
		// TODO: Assert OpenGL version
		F_GL_CHECK(glGetIntegerv(GL_MAJOR_VERSION, &major_));
		F_GL_CHECK(glGetIntegerv(GL_MAJOR_VERSION, &minor_));
		LOG_IF(major_ < 4, FATAL) << "OpenGL 4.x required!";
		// Get vendor string
		F_GL_CHECK(auto vendor_str = reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
		LOG_IF(vendor_str == nullptr, ERROR);
		gl_vendor_.assign(vendor_str);
		// Get renderer string
		F_GL_CHECK(auto renderer_str = reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
		LOG_IF(renderer_str == nullptr, ERROR);
		gl_renderer_.assign(renderer_str);
		// Get shading language version string
		F_GL_CHECK(auto shading_lang_ver = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
		LOG_IF(shading_lang_ver == nullptr, ERROR);
		gl_shading_lang_ver_.assign(shading_lang_ver);
		// Get OpenGL version string
		F_GL_CHECK(auto gl_ver_str = reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		LOG_IF(gl_ver_str == nullptr, ERROR);
		auto num_extensions = 0;
		F_GL_CHECK(glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions));
		this->exts_supported_.reserve(num_extensions);
		for (auto i = 0; i < num_extensions; i++)
		{
			F_GL_CHECK(this->exts_supported_.push_back(futils::ToLower(reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i)))));
		}
		LOG(INFO) << "\tVendor:\t" << gl_vendor_ << "\n\tRenderer:\t" << gl_renderer_ << "\n\tGLSL ver.:\t" <<
			gl_shading_lang_ver_ << "\n\tGL ver.:\t" << gl_ver_ << "\n\tExtensions:\t" << num_extensions;
	}

	FGlHelper::~FGlHelper()
	{
		LOG(INFO) << "FGlHelper dtor";
	}

	bool FGlHelper::IsExtensionSupported(const FString & ext_name)
	{
		const auto& found = std::find(exts_supported_.cbegin(), exts_supported_.cend(), futils::ToLower(ext_name));
		if (found != exts_supported_.cend())
		{
			LOG(WARNING) << "Extension " << ext_name << " is not supported!";
			return false;
		}
		return true;
	}

	bool FGlHelper::IsExtensionSupported(GlExtension ext)
	{
		// We assume that there are all possible values in the map.
		return IsExtensionSupported(ext_names_.at(ext));
	}

	bool FGlHelper::CheckErrors()
	{
		last_errors_.clear();
		GLenum err = GL_NO_ERROR;
		was_error_ = false;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			was_error_ = true;
			last_errors_ += GetGlErrorDescription(err) + "\n";
		}
		return was_error_;
	}

	FString FGlHelper::GetErrorsDescription()
	{
		return was_error_ ? GetLastErrors() : "No error.";
	}

	FString FGlHelper::GetGlErrorDescription(GLenum err)
	{
		switch (err)
		{
		case GL_NO_ERROR:
			return "No error.";
		case GL_INVALID_ENUM:
			return "Invalid enum.";
		case GL_INVALID_VALUE:
			return "Invalid value.";
		case GL_INVALID_OPERATION:
			return "Invalid operation.";
		case GL_STACK_OVERFLOW:
			return "Stack overflow.";
		case GL_STACK_UNDERFLOW:
			return "Stack underflow.";
		case GL_OUT_OF_MEMORY:
			return "Out of memory.";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "Invalid framebuffer operation.";
		case GL_CONTEXT_LOST:
			return "Context lost due to a graphics card reset.";
			//case GL_TABLE_TOO_LARGE:
		default:
			return "";
		}
	}
}
