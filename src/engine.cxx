#include "engine.hpp"
#include <iostream>

namespace FEngine {

	Engine::Engine() {
		// Construct logger
		this->logger_ = FLogger::GetInstance();
		
		FLogger::LoadConfiguration("loggers.cfg");
		LOG(INFO) << "========== LOG START  ==========";
	}
	Engine::~Engine() {

	}
}