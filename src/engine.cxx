#include <engine.hpp>

#include <SDL.h>

#include <helpers/f_sdl_helper.hpp>
#include <fcomponents/f_events_manager.hpp>
#include <fcomponents/f_scenes_manager.hpp>
#include <fcomponents/f_resource_loader.hpp>
#include "fcomponents/f_render_system.hpp"


namespace fengine
{
	Engine::Engine()
	{
		// Construct logger
		FLogger::GetInstance();	
		FLogger::LoadConfiguration("loggers.cfg");
		LOG(INFO) << "Engine ctor";
		LOG(INFO) << "========== LOG START  ==========";
		// Construct Settings
		this->settings_ = std::make_shared<FSettings>();
		// Construct SDL helper
		FSdlHelper::GetInstance();
		if (FSdlHelper::Initialize() != 0)
		{
			LOG(ERROR) << "SDL helper initialization error.";
			if (FSdlHelper::CheckError())
			{
				LOG(FATAL) << "SDL error: " << FSdlHelper::GetLastError();
			}
			LOG(FATAL) << "Terminating.";
		}

		// Construct Events Manager
		FEventsManager::GetInstance();
		// Construct resource loader
		FResourceLoader::GetInstance();
		// Construct scenes manager
		FScenesManager::GetInstance();
		// Construct renderer system
		FRenderSystem::GetInstance();

		/*auto ret_code = -1;
		switch (renderer_type)
		{
		case FRendererType::kOpenGlRenderer:
			break;
		case FRendererType::kDirectXRenderer:
			LOG(FATAL) << "DirectX Renderer is not supported yet!";
			break;
		default: break;
		}
		return ret_code;*/	
	}

	Engine::~Engine()
	{
		FResourceLoader::Release();
		FEventsManager::Release();
		FSdlHelper::Release();
		FLogger::Release();
		LOG(INFO) << "Engine dtor";
	}

	int Engine::Exec() const
	{
		main_loop_->OnInit();
		auto b = FRenderSystem::ExitRequest();
		while (main_loop_->is_running() && !FRenderSystem::ExitRequest())
		{
			main_loop_->OnPreUpdate();

			FEventsManager::HandleEvents();

			FRenderSystem::RenderFrame(0.0f);
				
			main_loop_->OnPostUpdate();
			SDL_Delay(1);
		}
		return main_loop_->OnTerminate();
	}
}
