#include "f_gl_helper.hpp"
#include <utils/f_utils.hpp>
#include <components/f_logger.hpp>

namespace fengine {

	// Map contains all names of extensions from GlExtension enum.
	const FMap<GlHelper::GlExtension, FString> GlHelper::ext_names_ = 
	{
		{ kGlExtFramebufferBlit, futils::ToLower("GL_EXT_Framebuffer_blit") }
	};

	GlHelper::GlHelper()
	{ 
		// TODO: Assert OpenGL version
		glGetIntegerv(GL_MAJOR_VERSION, &this->major_);
		glGetIntegerv(GL_MAJOR_VERSION, &this->minor_);
		
		// Get vendor string
		auto vendor_str = (const char*)glGetString(GL_VENDOR);
		LOG_IF(vendor_str != nullptr, ERROR);
		GlHelper::gl_vendor_.assign(vendor_str);
		// Get renderer string
		auto renderer_str = (const char*)glGetString(GL_RENDER);
		LOG_IF(renderer_str != nullptr, ERROR);
		GlHelper::gl_renderer_.assign(renderer_str);
		// Get shading language version string
		auto shading_lang_ver = (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
		LOG_IF(shading_lang_ver != nullptr, ERROR);
		GlHelper::gl_shading_lang_ver_.assign(shading_lang_ver);
		// Get OpenGL version string
		auto gl_ver_str = (const char*)glGetString(GL_VERSION);
		LOG_IF(gl_ver_str != nullptr, ERROR);
		GlHelper::gl_ver_.assign((const char*)glGetString(GL_VERSION));

		int num_extensions = 0;
		glGetIntegerv(GL_NUM_EXTENSIONS, &num_extensions);
		this->exts_supported_.reserve(num_extensions);
		for (int i = 0; i < num_extensions; i++)
		{
			this->exts_supported_.push_back(futils::ToLower((const char*)glGetStringi(GL_EXTENSIONS, i)));
		}
	}

	bool GlHelper::IsExtensionSupported(const FString & ext_name)
	{
		const auto& found = std::find(exts_supported_.cbegin(), exts_supported_.cend(), futils::ToLower(ext_name));
		if (found != exts_supported_.cend())
		{
			LOG(WARNING) << "Extension " << ext_name << " is not supported!";
			return false;
		}
		return true;
	}

	bool GlHelper::IsExtensionSupported(GlExtension ext)
	{
		// We assume that there are all possible values in the map.
		return GlHelper::IsExtensionSupported(GlHelper::ext_names_.at(ext));
	}
}
