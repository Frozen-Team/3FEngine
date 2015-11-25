#include "game_loop.hpp"

#include <fcomponents/f_logger.hpp>
#include <fcomponents/f_render_system.hpp>
#include <fcomponents/f_resource_loader.hpp>

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
	scene_one_ = std::make_shared<SceneOne>();
	fengine::FResourceLoader::LoadScene("scenes/camera_test.fbx", scene_one_);
	fengine::FRenderSystem::SetActiveScene(scene_one_);
	fengine::FRenderSystem::SetActiveCamera(scene_one_->GetCameras().at(0));
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
