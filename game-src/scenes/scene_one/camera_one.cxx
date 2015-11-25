#include "camera_one.hpp"

void CameraOne::OnKeyPressed(fengine::FKeyboardEvent& e)
{
	if (e.key() == fengine::fevents::kKeyW)
	{
		view_test_ = view_direction() / 5;
		std::cout << view_test_ << std::endl;
		move(view_test_);
		updateViewProjectionMatrix();
	}
	if (e.key() == fengine::fevents::kKeyS)
	{
		view_test_ = -view_direction() / 5;
		std::cout << view_test_ << std::endl;
		move(view_test_);
		updateViewProjectionMatrix();
	}

	if (e.key() == fengine::fevents::kKeyA)
	{
		move({ 0.1f, 0.0f, 0.0f });
		updateViewProjectionMatrix();
	}
	if (e.key() == fengine::fevents::kKeyD)
	{
		move({ -0.1f, 0.0f, 0.0f });
		updateViewProjectionMatrix();
	}
}

void CameraOne::OnKeyReleased(fengine::FKeyboardEvent& e)
{
}

void CameraOne::OnMouseButtonPressed(fengine::FMouseEvent& e)
{
	mouse_pressed_ = true;
	init_ = false;
}

void CameraOne::OnMouseButtonReleased(fengine::FMouseEvent& e)
{
	mouse_pressed_ = false;
	init_ = false;
}


void CameraOne::OnMouseMove(fengine::FMouseEvent& e)
{
	if (mouse_pressed_)
	{
		if (!init_)
		{
			init_ = true;
			mouse_prev_pos_ = e.pos();
		}

		rotate({ 0.0f, static_cast<float>((e.pos() - mouse_prev_pos_).x()) / 500, static_cast<float>((e.pos() - mouse_prev_pos_).y()) / 500 });
		
		/*Eigen::Affine3f transform = Eigen::Affine3f::Identity();
		transform.rotate(Eigen::AngleAxis<float>(static_cast<float>((e.pos() - mouse_prev_pos_).y()) / 500, Eigen::Vector3f::UnitX()));
		transform.rotate(Eigen::AngleAxis<float>(static_cast<float>((e.pos() - mouse_prev_pos_).x()) / 500, Eigen::Vector3f::UnitY()));
		Eigen::Matrix4f matrix = transform.matrix();
		view() = matrix * view();*/
		updateViewProjectionMatrix();

		mouse_prev_pos_ = e.pos();
	}
}

CameraOne::CameraOne() : view_test_(0.0, 0.0, 0.0), mouse_pressed_(false)
{
	// TODO: Get aspect ratio
	auto aspect_ration = 1.0f;
	SetPerspective(fengine::FAngle::Degrees(45.0f), aspect_ration, 0.1f, 10000.0f);
	LookAt({ 1.0, 1.0, 1.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
}
