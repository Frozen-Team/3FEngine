#include "f_gl_program.hpp"

#include <fcomponents/f_logger.hpp>
#include "f_gl_helper.hpp"

namespace fengine
{
	FGlProgram::FGlProgram(): program_id_(0), ready_(false)
	{
	}

	FGlProgram::~FGlProgram()
	{
		DeleteProgram();
	}

	void FGlProgram::AttachShader(const FGlShader& shader)
	{
		auto shader_id = shader.GetShaderId();
		F_GL_CHECK(glAttachShader(this->program_id_, shader_id));
		attached_shaders_.push_back(shader_id);
	}

	void FGlProgram::LinkProgram()
	{
		F_GL_CHECK(glLinkProgram(this->program_id_));
		auto link_status = GLint(0);
		F_GL_CHECK(glGetProgramiv(this->program_id_, GL_LINK_STATUS, &link_status));
		if (link_status == GL_FALSE)
		{
			DeleteProgram();
			LOG(FATAL) << "Link program error: \n" << FGlHelper::GetErrorsDescription();
		}
	}

	void FGlProgram::DeleteProgram()
	{
		if (this->program_id_ != 0)
		{
			F_GL_CHECK(glDeleteProgram(this->program_id_));
			auto delete_status = GLint(0);
			F_GL_CHECK(glGetProgramiv(this->program_id_, GL_DELETE_STATUS, &delete_status));
			LOG_IF(delete_status == GL_FALSE, ERROR) << "Delete program object error";
			this->program_id_ = 0;
		}
	}

	void FGlProgram::DetachShaders()
	{
		for (auto& shader : attached_shaders_)
		{
			F_GL_CHECK(glDetachShader(program_id_, shader));
			if (FGlHelper::CheckErrors())
			{
				LOG(FATAL) << "Attach shader error:\n" << FGlHelper::GetErrorsDescription();
			}
		}
	}

	void FGlProgram::Validate()
	{
		F_GL_CHECK(glValidateProgram(program_id_));
		auto validate_status = GLint(0);
		F_GL_CHECK(glGetProgramiv(this->program_id_, GL_VALIDATE_STATUS, &validate_status));
		if (validate_status == GL_FALSE)
		{
			DeleteProgram();
			LOG(FATAL) << "Validate program error: \n" << FGlHelper::GetErrorsDescription();
		}
	}

	void FGlProgram::Use() const
	{
		F_GL_CHECK(glUseProgram(this->program_id_));
	}

	GLint FGlProgram::GetAtributeLocation(const FString& attrib) const
	{
		F_GL_CHECK(auto location = glGetAttribLocation(this->program_id_, attrib.c_str()));
		LOG_IF(location == -1, ERROR) << "Cannot get attribute location. Attribute: " << attrib.c_str();
		return location;
	}

	GLint FGlProgram::GetUniformLocation(const FString & uniform) const
	{
		F_GL_CHECK(auto location = glGetUniformLocation(this->program_id_, uniform.c_str()));
		LOG_IF(location == -1, ERROR) << "Cannot get uniform location. Error: " << FGlHelper::GetErrorsDescription();
		return location;
	}

	void FGlProgram::Create()
	{
		LOG_IF(program_id_ != 0, FATAL) << "Program object is already created";
		this->program_id_ = glCreateProgram();
		LOG_IF(this->program_id_ == 0, FATAL) << "Cannot create program object:\n" << FGlHelper::GetErrorsDescription();
	}
}
