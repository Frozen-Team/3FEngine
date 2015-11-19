#ifndef _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_
#define _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_

#include <renderer/gl/f_gl_include.hpp>

#include <renderer/f_renderer_interface.hpp>
#include <renderer/gl/f_gl_program.hpp>
#include <scene/f_scene.hpp>
#include "f_gl_window.hpp"

namespace fengine
{
	class FGlRenderer : public FRendererInterface
	{
	public:
		
		FGlRenderer();
		virtual ~FGlRenderer() override;

		void Initialize();
		
		virtual void RenderFrame(float delta) override;

		virtual const FWindow& GetActiveWindow() override { return *window_; }
		
		void BufferizeScene(FShared<FScene> scene);

	private:
		void CreateWindowWithContext();

	private:
		FShared<FGlWindow> window_;

		struct geometry_
		{
			GLuint vbo;
			GLuint ibo;
			GLuint cbo;
			FShared<FGeometry> geometry;
		};

		FVector<geometry_> geometries_;
		FShared<FScene> scene_;

		FGlProgram program_;

		GLint vertex_loc_;
		GLint vertex_color_loc_;
		GLint mvp_loc_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_GL_F_GL_RENDERER_HPP_