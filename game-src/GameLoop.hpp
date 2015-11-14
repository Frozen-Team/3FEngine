#ifndef _3FENGINE_GAME_SRC_GAME_LOOP_HPP
#define _3FENGINE_GAME_SRC_GAME_LOOP_HPP

#include <f_main_loop_interface.hpp>

class GameLoop : public fengine::FMainLoopInterface
{
public:
	GameLoop();
	
	virtual ~GameLoop();

protected:
	void OnInit() override;

	int Exec() override;
};

#endif // _3FENGINE_GAME_SRC_GAME_LOOP_HPP