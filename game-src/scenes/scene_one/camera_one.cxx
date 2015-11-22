#include "camera_one.hpp"
#include "utils/f_entity_id_manager.hpp"
void CameraOne::OnKeyPressed(fengine::FKeyboardEvent& e)
{
	bool update = false;
	if (e.key() == fengine::fevents::kKeyW)
	{
		update = true;
		view_test_ = view_direction() / 10;
	}
	if (e.key() == fengine::fevents::kKeyS)
	{
		update = true;
		view_test_ = -view_direction() / 10;
	}
	std::cout << view_test_ << std::endl;

	if (e.key() == fengine::fevents::kKeyA)
	{
		update = true;
		view_test_ = {0.1f, 0.0f, 0.0f};
	}
	if (e.key() == fengine::fevents::kKeyD)
	{
		update = true;
		view_test_ = { -0.1f, 0.0f, 0.0f };
	}

	if (update)
	{
		Eigen::Affine3f transform = Eigen::Affine3f::Identity();
		transform.translation() = view_test_;
		Eigen::Matrix4f matrix = transform.matrix();
		view() = view() * matrix;
		updateViewProjectionMatrix();
	}
}

void CameraOne::OnKeyReleased(fengine::FKeyboardEvent& e)
{
}

// TODO: Mouse move
void CameraOne::OnMouseButtonPressed(fengine::FMouseEvent& e)
{
	mouse_pressed_ = true;
	init_ = false;
	//LOG(INFO) << "OnMouseButtonPressed";
}

void CameraOne::OnMouseButtonReleased(fengine::FMouseEvent& e)
{
	mouse_pressed_ = false;
	init_ = false;
	//LOG(INFO) << "OnMouseButtonReleased";
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
		Eigen::Affine3f transform = Eigen::Affine3f::Identity();
		transform.rotate(Eigen::AngleAxis<float>(static_cast<float>((e.pos() - mouse_prev_pos_).y()) / 500, Eigen::Vector3f::UnitX()));
		transform.rotate(Eigen::AngleAxis<float>(static_cast<float>((e.pos() - mouse_prev_pos_).x()) / 500, Eigen::Vector3f::UnitY()));
		Eigen::Matrix4f matrix = transform.matrix();
		view() = matrix * view();
		updateViewProjectionMatrix();

		mouse_prev_pos_ = e.pos();
	}
}

CameraOne::CameraOne() : fengine::FCamera(fengine::FEntityIdManager::GenerateId()), view_test_(0.0, 0.0, 0.0), mouse_pressed_(false)
{
	// TODO: Get aspect ratio
	auto aspect_ration = 1.0f;
	SetPerspective(fengine::FAngle::Degrees(45.0f), aspect_ration, 0.1f, 10000.0f);
	LookAt({ 1.0, 1.0, 1.0 }, { 0.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 });
}
