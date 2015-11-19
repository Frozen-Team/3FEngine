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
		glAttachShader(this->program_id_, shader_id);
		LOG_IF(FGlHelper::CheckErrors(), FATAL) << "Attach shader error:\n" << FGlHelper::GetErrorsDescription();
		attached_shaders_.push_back(shader_id);
	}

	void FGlProgram::LinkProgram()
	{
		glLinkProgram(this->program_id_);
		auto link_status = GLint(0);
		glGetProgramiv(this->program_id_, GL_LINK_STATUS, &link_status);
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
			glDeleteProgram(this->program_id_);
			auto delete_status = GLint(0);
			glGetProgramiv(this->program_id_, GL_DELETE_STATUS, &delete_status);
			LOG_IF(delete_status == GL_FALSE, ERROR) << "Delete program object error:\n" << FGlHelper::GetErrorsDescription();
			this->program_id_ = 0;
		}
	}

	void FGlProgram::DetachShaders()
	{
		for (auto& shader : attached_shaders_)
		{
			glDetachShader(program_id_, shader);
			if (FGlHelper::CheckErrors())
			{
				LOG(FATAL) << "Attach shader error:\n" << FGlHelper::GetErrorsDescription();
			}
		}
	}

	void FGlProgram::Validate()
	{
		glValidateProgram(program_id_);
		auto validate_status = GLint(0);
		glGetProgramiv(this->program_id_, GL_VALIDATE_STATUS, &validate_status);
		if (validate_status == GL_FALSE)
		{
			DeleteProgram();
			LOG(FATAL) << "Validate program error: \n" << FGlHelper::GetErrorsDescription();
		}
	}

	void FGlProgram::Use()
	{
		glUseProgram(this->program_id_);
	}

	GLint FGlProgram::GetAtributeLocation(const FString& attrib)
	{
		GLint location = glGetAttribLocation(this->program_id_, attrib.c_str());
		LOG_IF(location == -1, ERROR) << "Cannot get attribute location. Error: " << FGlHelper::GetErrorsDescription();
		return location;
	}

	GLint FGlProgram::GetUniformLocation(const FString & uniform)
	{
		GLint location = glGetUniformLocation(this->program_id_, uniform.c_str());
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
