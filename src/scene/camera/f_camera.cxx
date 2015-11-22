#include "f_camera.hpp"
#include <limits>
#include "utils/f_utils.hpp"
#include <utils/f_entity_id_manager.hpp>

namespace fengine
{
	// TODO: Retrieve id, name
	FCamera::FCamera(const FEntityId& id) : FCamera(id, FPoint3f::Zero(), FPoint3f::Zero(), FPoint3f(1.0f, 1.0f, 1.0f))
	{}

	FCamera::FCamera(const FEntityId& id, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale)
		: FEntity(id, FEntityType::kCamera, transition, rotation, scale)
	{
		view_ = Eigen::Matrix4f::Zero(4, 4);
		this->proj_type_ = ProjectionType::kPerspective;
		this->projection_ = FMatrix4f::Zero(4, 4);
		this->view_projection_ = FMatrix4f::Zero(4, 4);
		this->target_entity_ = nullptr;
		
		this->aperture_ = FPoint2f(0.0f, 0.0f);
		this->film_aspect_ratio_ = 1.3333333f;
		this->focal_length_ = 1.0f;
		this->aspect_ratio_ = 1.3333333f;
		this->znear_ = 0.1f;
		this->zfar_ = 10000.0f;

		this->fovy_ = 0.0f;
		this->ortho_left_ = 0.0f;
		this->ortho_right_ = 0.0f;
		this->ortho_bottom_ = 0.0f;
		this->ortho_top_ = 0.0f;
		LookAt(FPoint3f(0.0f, 0.0f, 0.0f));
	}
	/*
		Move camera at position \param pos and set target \param target
	*/
	void FCamera::LookAt(const FPoint3f& pos, const FPoint3f& target, const FPoint3f& up)
	{
		this->SetTransition(pos);
		this->up_vector_ = up;
		LookAt(target);	
	}

	void FCamera::LookAt(const FPoint3f & target)
	{
		this->target_point_ = target;

		auto position = this->GetTransition();

		FMatrix3f R;
		R.col(2) = (position - target_point_).normalized();
		R.col(0) = up_vector_.cross(R.col(2)).normalized();
		R.col(1) = R.col(2).cross(R.col(0));
		view_.topLeftCorner<3, 3>() = R.transpose();
		view_.topRightCorner<3, 1>() = -R.transpose() * position;
		view_(3, 3) = 1.0f;

		updateViewProjectionMatrix();
	}

	void FCamera::LookAt(FShared<FEntity> target)
	{
		this->target_entity_ = target;
		LookAt(target != nullptr ? target->GetTransition() : FPoint3f(0.0f, 0.0f, 0.0f));
	}

	void FCamera::SetPerspective(const FAngle& fovy, float aspect, float znear, float zfar)
	{
		this->fovy_ = fovy.radians();
		this->aspect_ratio_ = aspect;
		this->znear_ = znear;
		this->zfar_ = zfar;
		UpdatePerspective();
	}

	void FCamera::UpdatePerspective()
	{
		auto range = zfar_ - znear_;
		LOG_IF(futils::almost_equal(range, static_cast<decltype(range)>(0.0), 4), FATAL) << "";
		auto invtan = 1.0f / tan(fovy_ * 0.5f);
		this->projection_ = Eigen::MatrixXf::Zero(4, 4);

		projection_(0, 0) = invtan / aspect_ratio_;
		projection_(1, 1) = invtan;
		projection_(2, 2) = -(znear_ + zfar_) / range;
		projection_(3, 2) = -1;
		projection_(2, 3) = -2 * znear_ * zfar_ / range;
		projection_(3, 3) = 0;

		updateViewProjectionMatrix();
	}

	void FCamera::SetOrtho(float left, float right, float bottom, float top, float zfar, float znear)
	{
		this->ortho_left_ = left;
		this->ortho_right_ = right;
		this->ortho_bottom_ = bottom;
		this->ortho_top_ = top;
		this->zfar_ = zfar;
		this->znear_ = znear;
		UpdateOrtho();
	}

	void FCamera::UpdateOrtho()
	{
		this->projection_ = FMatrix4f::Identity();

		projection_(0, 0) = 2.0f / (this->ortho_right_ - this->ortho_left_);
		projection_(1, 1) = 2.0f / (this->ortho_top_ - this->ortho_bottom_);
		projection_(2, 2) = -2.0f / (zfar_ - znear_);
		projection_(3, 0) = -(this->ortho_right_ + this->ortho_left_) / (this->ortho_right_ - this->ortho_left_);
		projection_(3, 1) = -(this->ortho_top_ + this->ortho_bottom_) / (this->ortho_top_ - this->ortho_bottom_);
		projection_(3, 2) = -(this->zfar_ + this->znear_) / (this->zfar_ - this->znear_);
		//projection_(3, 3) = 1.0f;

		updateViewProjectionMatrix();
	}

	void FCamera::set_aperture(const FPoint2f& apperture)
	{
		this->aperture_ = apperture;
	}

	void FCamera::set_aperture(float width, float height)
	{
		this->aperture_ = { width, height };
	}

	void FCamera::set_film_aspect_ratio(float film_aspect_ratio)
	{
		this->film_aspect_ratio_ = film_aspect_ratio;
	}

	void FCamera::set_focal_length(float focal_length)
	{
		this->focal_length_ = focal_length;
	}

	void FCamera::set_znear(float znear)
	{
		this->znear_ = znear;
		UpdatePerspective();
	}

	void FCamera::set_zfar(float zfar)
	{
		this->zfar_ = zfar;
		UpdatePerspective();
	}

	void FCamera::set_fovy(const FAngle & angle)
	{
		this->fovy_ = angle.radians();
		UpdatePerspective();
	}

	void FCamera::set_aspect_ratio(float aspect_ratio)
	{
		this->aspect_ratio_ = aspect_ratio;
		UpdatePerspective();
	}

	void FCamera::updateViewProjectionMatrix()
	{
		this->view_projection_ =  projection_ * view_;
	}
}
