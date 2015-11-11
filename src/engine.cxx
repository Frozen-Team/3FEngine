#include <iostream>

#include "engine.hpp"


namespace fengine
{
	Engine::Engine()
	{
		// Construct logger
		this->logger_ = FLogger::GetInstance();	
		FLogger::LoadConfiguration("loggers.cfg");
		LOG(INFO) << "========== LOG START  ==========";
		// Construct Settings
		this->settings_ = std::make_shared<FSettings>();

		if (this->sdl_helper_->Initialize() != 0)
		{
			LOG(ERROR) << "SDL helper initialization error.";
			if (this->sdl_helper_->CheckError())
			{
				LOG(FATAL) << "SDL error: " << this->sdl_helper_->GetLastError();
			}
			LOG(FATAL) << "Terminating.";
		}

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

		// Construct Events Manager
		this->events_manager_ = FEventsManager::GetInstance();
	}
	Engine::~Engine() {}

	void Engine::Initialize(FUnique<FMainLoopInterface> main_loop)
	{
		LOG_IF(!main_loop_, FATAL) << "Passed main loop is null.";
		main_loop_ = std::move(main_loop);	
	}

	int Engine::Exec() const
	{
		LOG_IF(!main_loop_, FATAL) << "Engine is not initialized: Main loop is not set.";
		main_loop_->OnInit();
		return main_loop_->Run();
	}
}
