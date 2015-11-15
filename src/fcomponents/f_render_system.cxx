#include "f_render_system.hpp"

namespace fengine
{
	F_STATIC_DECL_INIT(FRenderSystem, renderer_);
	F_STATIC_DECL_INIT(FRenderSystem, active_scene_);
	F_STATIC_DECL_INIT(FRenderSystem, active_camera_);

	FRenderSystem::FRenderSystem()
	{
		LOG(INFO) << "FRenderSystem ctor";
	}

	FRenderSystem::~FRenderSystem()
	{
		LOG(INFO) << "FRenderSystem dtor";
	}

	void FRenderSystem::SetActiveScene(FShared<FScene> scene)
	{
		active_scene_ = scene;
	}

	void FRenderSystem::SetActiveCamera(FShared<FCamera> camera)
	{
		active_camera_ = camera;
	}

	void FRenderSystem::RenderFrame(float delta)
	{
		//LOG_IF(active_camera_ == nullptr, FATAL) << "Active camera is not set.";
		//LOG_IF(active_scene_ == nullptr, FATAL) << "Active scene is not set.";
		LOG_IF(renderer_ == nullptr, FATAL) << "Invalid renderer";
		renderer_->RenderFrame(delta);
	}
}
