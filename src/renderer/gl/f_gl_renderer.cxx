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
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetSwapInterval(-1);
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
		program_.DetachShaders();
		program_.Validate();

		this->vertex_loc_ = program_.GetAtributeLocation("vertex");
		this->vertex_color_loc_ = program_.GetAtributeLocation("vertex_color");
		this->mvp_loc_ = program_.GetUniformLocation("mvp");

		glEnable(GL_BLEND);
		//glEnable(GL_DEPTH_TEST);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
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

			auto& v = geometry->vertices().vertices();

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, v.size() * sizeof(float), v.data(), GL_STATIC_DRAW);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			auto& i = geometry->indices().vertices();

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, i.size() * sizeof(float), i.data(), GL_STATIC_DRAW);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			auto& c = geometry->uvs().vertices();

			glGenBuffers(1, &cbo);
			glBindBuffer(GL_ARRAY_BUFFER, cbo);
			glBufferData(GL_ARRAY_BUFFER, c.size() * sizeof(float), c.data(), GL_STATIC_DRAW);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			geometries_.push_back({ vbo, ibo, cbo, geometry });
		}
		this->program_.Use();
		glUniformMatrix4fv(mvp_loc_, 1, GL_FALSE, scene->GetCameras().at(0)->view_projection().data());
		auto d = scene->GetCameras().at(0)->view_projection();
		LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
	}

	void FGlRenderer::RenderFrame(float delta)
	{
		//glClearColor(float(rand() % 256) / 256, float(rand() % 256) / 256, float(rand() % 256) / 256, 1.0);
		glClearColor(1.0, 1.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
		program_.Use();
		LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
		for (auto it = geometries_.begin(); it != geometries_.end(); ++it)
		{
			glEnableVertexAttribArray(vertex_loc_);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			// Describe our vertices array to OpenGL (it can't guess its format automatically)
			glBindBuffer(GL_ARRAY_BUFFER, it->vbo);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			glVertexAttribPointer(
				vertex_loc_, // attribute
				3,                 // number of elements per vertex, here (x,y,z)
				GL_FLOAT,          // the type of each element
				GL_FALSE,          // take our values as-is
				0,                 // no extra data between each position
				0                  // offset of first element
				);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			glEnableVertexAttribArray(vertex_color_loc_);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			glBindBuffer(GL_ARRAY_BUFFER, it->cbo);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			glVertexAttribPointer(vertex_color_loc_, 3, GL_FLOAT, GL_FALSE, 0, 0);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			/* Push each element in buffer_vertices to the vertex shader */
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, it->ibo);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			int size;
			glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			glDrawElements(GL_TRIANGLES, size / sizeof(GLushort), GL_UNSIGNED_SHORT, 0);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();

			glDisableVertexAttribArray(vertex_loc_);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
			glDisableVertexAttribArray(vertex_color_loc_);
			LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
		}
		LOG_IF(FGlHelper::CheckErrors(), FATAL) << "OpenGL error: " << FGlHelper::GetLastErrors();
		window_->SwapWindow();
	}

	void FGlRenderer::CreateWindowWithContext()
	{
		window_ = std::make_shared<FGlWindow>("First rendering", FPoint2i(500, 500), FPoint2i(500, 500), fgui::WindowFlags(fgui::WindowFlag::kWindowOpenGl));
		FEventsManager::Register(window_);
	}
}
