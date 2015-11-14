#include <engine.hpp>
#include "fcomponents/f_logger.hpp"
#include "helpers/f_sdl_helper.hpp"
#include "fcomponents/f_events_manager.hpp"


namespace fengine
{
	Engine::Engine()
	{
		// Construct logger
		FLogger::GetInstance();	
		FLogger::LoadConfiguration("loggers.cfg");
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
		FEventsManager::Release();
		FSdlHelper::Release();
		FLogger::Release();
	}

	int Engine::Exec() const
	{
		LOG_IF(!main_loop_, FATAL) << "Engine is not initialized: Main loop is not set.";
		main_loop_->OnInit();
		return main_loop_->Run();
	}
}
