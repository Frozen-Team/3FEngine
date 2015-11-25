#include "camera_one.hpp"
#include "utils/f_entity_id_manager.hpp"
void CameraOne::OnKeyPressed(fengine::FKeyboardEvent& e)
{
	if (e.key() == fengine::fevents::kKeyW)
	{
		velocity_.z() = 0.3f;
	}
	if (e.key() == fengine::fevents::kKeyS)
	{
		velocity_.z() = -0.3f;
	}
	if (e.key() == fengine::fevents::kKeyA)
	{
		velocity_.x() = 0.3f;
	}
	if (e.key() == fengine::fevents::kKeyD)
	{
		velocity_.x() = -0.3f;
	}
	move(velocity_);
	updateViewProjectionMatrix();
}

void CameraOne::OnKeyReleased(fengine::FKeyboardEvent& e)
{
	if (e.key() == fengine::fevents::kKeyW)
	{
		velocity_.z() = 0.0f;
	}
	if (e.key() == fengine::fevents::kKeyS)
	{
		velocity_.z() = 0.0f;
	}

	if (e.key() == fengine::fevents::kKeyA)
	{
		velocity_.x() = 0.0f;
	}
	if (e.key() == fengine::fevents::kKeyD)
	{
		velocity_.x() = 0.0f;
	}
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

		rotate({ static_cast<float>((e.pos() - mouse_prev_pos_).y()) / 500, static_cast<float>((e.pos() - mouse_prev_pos_).x()) / 500, 0.0f });
		
		/*Eigen::Affine3f transform = Eigen::Affine3f::Identity();
		transform.rotate(Eigen::AngleAxis<float>(static_cast<float>((e.pos() - mouse_prev_pos_).y()) / 500, Eigen::Vector3f::UnitX()));
		transform.rotate(Eigen::AngleAxis<float>(static_cast<float>((e.pos() - mouse_prev_pos_).x()) / 500, Eigen::Vector3f::UnitY()));
		Eigen::Matrix4f matrix = transform.matrix();
		view() = matrix * view();*/
		updateViewProjectionMatrix();

		mouse_prev_pos_ = e.pos();
	}
}

CameraOne::CameraOne() : fengine::FCamera(fengine::FEntityIdManager::GenerateId()), mouse_pressed_(false), velocity_{0.0f, 0.0f, 0.0f}
{
	// TODO: Get aspect ratio
	auto aspect_ration = 1.0f;
	SetPerspective(fengine::FAngle::Degrees(45.0f), aspect_ration, 0.1f, 10000.0f);
	LookAt({ 10.0, 10.0, 10.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
}
