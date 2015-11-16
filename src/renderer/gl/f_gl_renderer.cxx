#include "f_gl_renderer.hpp"

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
	}

	FGlRenderer::~FGlRenderer()
	{
		//FGlHelper::Release();
		LOG(INFO) << "FGlRenderer dtor";
	}

	void FGlRenderer::RenderFrame(float delta)
	{
		glClearColor(float(rand() % 256) / 256, float(rand() % 256) / 256, float(rand() % 256) / 256, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		window_->SwapWindow();
	}

	void FGlRenderer::CreateWindowWithContext()
	{
		window_ = std::make_shared<FGlWindow>("First rendering", FPoint2i(500, 500), FPoint2i(800, 800), fgui::WindowFlags(fgui::WindowFlag::kWindowOpenGl));
		FEventsManager::Register(window_);
	}
}
