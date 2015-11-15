#include "camera_one.hpp"

// TODO: Mouse move
void CameraOne::OnMouseButtonPressed(fengine::FMouseEvent& e)
{
}

void CameraOne::OnMouseButtonReleased(fengine::FMouseEvent& e)
{
}


void CameraOne::OnMouseMove(fengine::FMouseEvent& e)
{
}

CameraOne::CameraOne()
{
	// TODO: Get aspect ratio
	auto aspect_ration = 1.0f;
	SetPerspective(fengine::FAngle::Degrees(45.0f), aspect_ration, 0.1f, 10.0f);
}
