#include "GameLoop.hpp"

#include <fcomponents/f_logger.hpp>

GameLoop::GameLoop()
	: FMainLoopInterface(true)
{
}

GameLoop::~GameLoop()
{
}

void GameLoop::OnInit()
{
	LOG(INFO) << "GameLoop init";
}

int GameLoop::Exec()
{





	return 100500;
}
