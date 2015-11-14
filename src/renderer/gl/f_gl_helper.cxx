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
	FString FGlHelper::gl_ver_;
	FString FGlHelper::gl_shading_lang_ver_;

	FGlHelper::FGlHelper()
	{

		GLenum rev;
		glewExperimental = GL_TRUE;
		auto err = GLEW_OK;
		LOG_IF((err = glewInit()) != GLEW_OK, FATAL) << "GLEW initialization error: " << glewGetErrorString(err);

		last_errors_.reserve(256);
		// TODO: Assert OpenGL version
		glGetIntegerv(GL_MAJOR_VERSION, &this->major_);
		glGetIntegerv(GL_MAJOR_VERSION, &this->minor_);
		
		// Get vendor string
		auto vendor_str = reinterpret_cast<const char*>(glGetString(GL_VENDOR));
		LOG_IF(vendor_str != nullptr, ERROR);
		gl_vendor_.assign(vendor_str);
		// Get renderer string
		auto renderer_str = reinterpret_cast<const char*>(glGetString(GL_RENDER));
		LOG_IF(renderer_str != nullptr, ERROR);
		gl_renderer_.assign(renderer_str);
		// Get shading language version string
		auto shading_lang_ver = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));
		LOG_IF(shading_lang_ver != nullptr, ERROR);
		gl_shading_lang_ver_.assign(shading_lang_ver);
		// Get OpenGL version string
		auto gl_ver_str = reinterpret_cast<const char*>(glGetString(GL_VERSION));
		LOG_IF(gl_ver_str != nullptr, ERROR);
		gl_ver_.assign(reinterpret_cast<const char*>(glGetString(GL_VERSION)));

		auto num_extensions = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
		this->exts_supported_.reserve(num_extensions);
		for (auto i = 0; i < num_extensions; i++)
		{
			this->exts_supported_.push_back(futils::ToLower(reinterpret_cast<const char*>(glGetStringi(GL_EXTENSIONS, i))));
		}
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
		auto was_error = false;
		while ((err = glGetError()) != GL_NO_ERROR)
		{
			was_error = true;
			last_errors_ += GetGlErrorDescription(err) + "\n";
		}
		return was_error;
	}

	FString FGlHelper::GetErrorsDescription()
	{
		return CheckErrors() ? GetLastErrors() : "No error description.";
	}

	FString FGlHelper::GetGlErrorDescription(GLenum err)
	{
		switch (err)
		{
		case GL_NO_ERROR:
			return "OGL: No error.";
		case GL_INVALID_ENUM:
			return "OGL: Invalid enum.";
		case GL_INVALID_VALUE:
			return "OGL: Invalid value.";
		case GL_INVALID_OPERATION:
			return "OGL: Invalid operation.";
		case GL_STACK_OVERFLOW:
			return "OGL: Stack overflow.";
		case GL_STACK_UNDERFLOW:
			return "OGL: Stack underflow.";
		case GL_OUT_OF_MEMORY:
			return "OGL: Out of memory.";
		case GL_INVALID_FRAMEBUFFER_OPERATION:
			return "OGL: Invalid framebuffer operation.";
		case GL_CONTEXT_LOST:
			return "OGL: Context lost due to a graphics card reset.";
			//case GL_TABLE_TOO_LARGE:
		default:
			return "";
		}
	}
}
