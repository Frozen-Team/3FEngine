#include "game_loop.hpp"

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

void GameLoop::OnPreUpdate()
{
}

void GameLoop::OnPostUpdate()
{

}


int GameLoop::OnTerminate()
{
	return 0;
}
