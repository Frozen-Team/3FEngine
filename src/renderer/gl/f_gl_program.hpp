#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_PROGRAM_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_PROGRAM_HPP_

#include <renderer/gl/f_gl_include.hpp>
#include <renderer/gl/f_gl_shader.hpp>

namespace fengine
{
	class FGlProgram
	{
	public:
		FGlProgram();

		~FGlProgram();

		// TODO: glBindAttribLocation, glBindFragDataLocation... and so on
		// TODO: Program stages

		void AttachShader(const FGlShader& shader);

		void LinkProgram();

		void DeleteProgram();

		void DetachShaders();

		void Validate();

	private:
		void Create();

	private:
		GLuint program_id_;
		bool ready_;
		FVector<GLuint> attached_shaders_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_PROGRAM_HPP_