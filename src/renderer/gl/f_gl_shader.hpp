#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_SHADER_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_SHADER_HPP_

#include <renderer/gl/f_gl_include.hpp>
#include <utils/f_typedefs.hpp>

enum class ShaderType
{
	kVertexShader,
	kFragmentShader,
	kGeometryShader,
	kTessControlShader,
	kTessEvaluationShader,
	kComputeShader
};

namespace fengine
{
	class FGlShader
	{

	public:
		explicit FGlShader(ShaderType type, bool separable = false);
		~FGlShader();

		void BindSource(const FString& src) const;

		void Compile() const;

		ShaderType type() const noexcept { return type_; }

		friend class FGlProgram;
	private:
		void Create();

		GLuint GetShaderId() const { return shader_id_; }

	private:
		GLuint gl_shader_type_;
		ShaderType type_;
		GLuint shader_id_;
		bool separable_;
		bool compiled_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_SHADER_HPP_