#ifndef _3FENGINE_GAME_SRC_GAME_LOOP_HPP
#define _3FENGINE_GAME_SRC_GAME_LOOP_HPP

#include <f_main_loop_interface.hpp>
#include <utils/f_typedefs.hpp>
#include "scenes/scene_one/scene_one.hpp"

class GameLoop : public fengine::FMainLoopInterface
{
public:
	GameLoop();
	
	virtual ~GameLoop();

protected:
	void OnInit() override;

	void OnPreUpdate() override;

	void OnPostUpdate() override;

	int OnTerminate() override;

private:
	fengine::FShared<SceneOne> scene_one_;
};

#endif // _3FENGINE_GAME_SRC_GAME_LOOP_HPP