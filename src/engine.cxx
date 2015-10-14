#include "engine.hpp"
#include <iostream>

namespace FEngine {
	Engine::Engine() {
		// Construct logger
		this->logger_ = FLogger::GetInstance();

	}
	Engine::~Engine() {

	}

	//template<>
	//std::shared_ptr<Engine> Utils::Singleton<Engine>::instance = nullptr;
}