#include "f_gl_shader.hpp"
#include <fcomponents/f_logger.hpp>
#include <utils/f_typedefs.hpp>
#include <renderer/gl/f_gl_helper.hpp>

namespace fengine
{
	constexpr GLuint ToGlShaderType(ShaderType t)
	{
		return	t == ShaderType::kVertexShader ? GL_VERTEX_SHADER :
			t == ShaderType::kFragmentShader ? GL_FRAGMENT_SHADER :
			t == ShaderType::kTessControlShader ? GL_TESS_CONTROL_SHADER :
			t == ShaderType::kTessEvaluationShader ? GL_TESS_EVALUATION_SHADER :
			t == ShaderType::kGeometryShader ? GL_GEOMETRY_SHADER :
			t == ShaderType::kComputeShader ? GL_COMPUTE_SHADER : GL_ZERO;
	}
	FGlShader::FGlShader(ShaderType type, bool separable)
		: gl_shader_type_(ToGlShaderType(type)), type_(type), shader_id_(0), separable_(separable), compiled_(false)
	{
		// TODO: Check if shader is available to be created on current GPU
		Create();
	}

	FGlShader::~FGlShader()
	{
		if (this->shader_id_ != 0)
		{
			F_GL_CHECK(glDeleteShader(this->shader_id_));
			this->shader_id_ = 0;
		}
	}

	void FGlShader::BindSource(const FString& src) const
	{
		auto source = src.c_str();
		F_GL_CHECK(glShaderSource(this->shader_id_, 1, &source, nullptr));
	}

	void FGlShader::Compile() const
	{
		F_GL_CHECK(glCompileShader(this->shader_id_));
		auto compiled = GLint(0);
		F_GL_CHECK(glGetShaderiv(this->shader_id_, GL_COMPILE_STATUS, &compiled));
		if (compiled == GL_FALSE)
		{
			auto log_length = GLint(0);
			F_GL_CHECK(glGetShaderiv(this->shader_id_, GL_INFO_LOG_LENGTH, &log_length));
			FString log_str(log_length, ' ');
			F_GL_CHECK(glGetShaderInfoLog(this->shader_id_, log_length, &log_length, &log_str[0]));
			LOG(FATAL) << "Shader object compilation error:\n" << log_str; 
		}
	}

	void FGlShader::Create()
	{
		LOG_IF(shader_id_ != 0, FATAL) << "Shader object is already created";
		F_GL_CHECK(this->shader_id_ = glCreateShader(gl_shader_type_));
		LOG_IF(this->shader_id_ == 0, FATAL) << "Cannot create shader object.";
		if (this->separable_)
		{
			// if GL_VERSION >= 4.1
			F_GL_CHECK(glProgramParameteri(this->shader_id_, GL_PROGRAM_SEPARABLE, GL_TRUE));
		}
	}
}
