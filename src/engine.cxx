#include <iostream>

#include "engine.hpp"


namespace fengine {
	Engine::Engine() {
		// Construct logger
		this->logger_ = FLogger::GetInstance();
		
		FLogger::LoadConfiguration("loggers.cfg");
		LOG(INFO) << "========== LOG START  ==========";

		this->settings_ = std::make_shared<FSettings>();
	}
	Engine::~Engine() {

	}
}