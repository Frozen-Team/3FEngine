#include "f_gl_renderer.hpp"

#include <utils/f_file_loader.hpp>

#include <renderer/gl/f_gl_shader.hpp>

#include <fcomponents/f_logger.hpp>
#include "f_gl_helper.hpp"

namespace fengine
{
	FGlRenderer::FGlRenderer()
	{
		LOG(INFO) << "FGlRenderer ctor";
		//SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetSwapInterval(0);
		CreateWindowWithContext();
		// Construct OpenGL helper
		FGlHelper::GetInstance();

		Initialize();
	}

	FGlRenderer::~FGlRenderer()
	{
		LOG(INFO) << "FGlRenderer dtor";
		FGlHelper::Release();	
	}

	void FGlRenderer::Initialize()
	{
		// Compile shaders
		FGlShader fragment(ShaderType::kFragmentShader);

		fragment.BindSource(futils::FFileLoader("renderer/gl/shaders/first_shader.f.glsl").ToString());
		fragment.Compile();

		FGlShader vertex(ShaderType::kVertexShader);

		vertex.BindSource(futils::FFileLoader("renderer/gl/shaders/first_shader.v.glsl").ToString());
		vertex.Compile();

		program_.Create();

		program_.AttachShader(fragment);
		program_.AttachShader(vertex);
		program_.LinkProgram();
		//program_.DetachShaders();
		//program_.Validate();

		this->vertex_loc_ = program_.GetAtributeLocation("vertex");
		this->vertex_color_loc_ = program_.GetAtributeLocation("vertex_color");
		this->mvp_loc_ = program_.GetUniformLocation("mvp");

		F_GL_CHECK(glEnable(GL_BLEND));
		F_GL_CHECK(glEnable(GL_DEPTH_TEST));
		F_GL_CHECK(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	}

	void FGlRenderer::BufferizeScene(FShared<FScene> scene)
	{
		this->scene_ = scene;
		for (auto mesh : scene_->GetMeshes())
		{
			GLuint vbo = 0;
			GLuint ibo = 0;
			GLuint cbo = 0;

			auto geometry = mesh->GetGeometry(0.0f);

			auto& v = geometry->vertices().data();

			F_GL_CHECK(glGenBuffers(1, &vbo));
			F_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
			F_GL_CHECK(glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data(), GL_STATIC_DRAW));
			auto& i = geometry->indices().data();

			F_GL_CHECK(glGenBuffers(1, &ibo));
			F_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
			F_GL_CHECK(glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(float), i.data(), GL_STATIC_DRAW));
			auto& c = geometry->uvs().data();

			F_GL_CHECK(glGenBuffers(1, &cbo));
			F_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cbo));
			F_GL_CHECK(glBufferData(GL_ARRAY_BUFFER, c.size() * sizeof(float), c.data(), GL_STATIC_DRAW));

			GLuint vao = 0;
			F_GL_CHECK(glGenVertexArrays(1, &vao));
			F_GL_CHECK(glBindVertexArray(vao));

			F_GL_CHECK(glEnableVertexAttribArray(vertex_loc_));
			F_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, vbo));
			F_GL_CHECK(glVertexAttribPointer(vertex_loc_, 3, GL_FLOAT, GL_FALSE, 0, 0));

			F_GL_CHECK(glEnableVertexAttribArray(vertex_color_loc_));
			F_GL_CHECK(glBindBuffer(GL_ARRAY_BUFFER, cbo));
			F_GL_CHECK(glVertexAttribPointer(vertex_color_loc_, 3, GL_FLOAT, GL_FALSE, 0, nullptr));

			F_GL_CHECK(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));


			geometries_.push_back({ vao, vbo, ibo, cbo, geometry });
		}
		this->program_.Use();
		F_GL_CHECK(glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, scene_->GetCameras().at(0)->view_projection().data()));
		auto d = scene->GetCameras().at(0)->view_projection();
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void FGlRenderer::RenderFrame(float delta)
	{
		//glClearColor(float(rand() % 256) / 256, float(rand() % 256) / 256, float(rand() % 256) / 256, 1.0);
		glClearColor(1.0, 1.0, .5, 1.0);
		F_GL_CHECK(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		program_.Use();
		for (auto it = geometries_.begin(); it != geometries_.end(); ++it)
		{
			F_GL_CHECK(glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, scene_->GetCameras().at(0)->view_projection().data()));
			glBindVertexArray(it->vao);
			glDrawArrays(GL_TRIANGLES, 0, 24);
			
			/*int size;
			F_GL_CHECK(glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size));
			F_GL_CHECK(glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, nullptr));

			F_GL_CHECK(glDisableVertexAttribArray(vertex_loc_));
			F_GL_CHECK(glDisableVertexAttribArray(vertex_color_loc_));*/
		}
		window_->SwapWindow();
	}

	void FGlRenderer::CreateWindowWithContext()
	{
		window_ = std::make_shared<FGlWindow>("First rendering", FPoint2i(500, 500), FPoint2i(1000, 1000), fgui::WindowFlags(fgui::WindowFlag::kWindowOpenGl));
		FEventsManager::Register(window_);
	}
}
