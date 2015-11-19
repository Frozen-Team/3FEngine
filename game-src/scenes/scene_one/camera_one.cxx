#include "camera_one.hpp"

// TODO: Mouse move
void CameraOne::OnMouseButtonPressed(fengine::FMouseEvent& e)
{
	//LOG(INFO) << "OnMouseButtonPressed";
}

void CameraOne::OnMouseButtonReleased(fengine::FMouseEvent& e)
{
	//LOG(INFO) << "OnMouseButtonReleased";
}


void CameraOne::OnMouseMove(fengine::FMouseEvent& e)
{
	//LOG(INFO) << "OnMouseMove";
}

CameraOne::CameraOne()
{
	// TODO: Get aspect ratio
	auto aspect_ration = 1.0f;
	SetPerspective(fengine::FAngle::Degrees(45.0f), aspect_ration, 0.1f, 100.0f);
	LookAt({ 0.0, 2.0, 0.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
}
