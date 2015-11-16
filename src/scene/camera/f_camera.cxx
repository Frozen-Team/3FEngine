#include "f_camera.hpp"
#include "utils/f_utils.hpp"

namespace fengine
{
	FCamera::FCamera()
	{
		this->set_type(FEntityType::kCamera);
		this->ResetSecondaryAttrToDefault();
	}

	FCamera::FCamera(uint64_t id, const FString& name, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale)
		: FEntity(id, name, FEntityType::kCamera, transition, rotation, scale)
	{
		this->ResetSecondaryAttrToDefault();
	}


	void FCamera::ResetSecondaryAttrToDefault()
	{
		set_target(nullptr);
		set_aperture(FPoint2f(0.0f, 0.0f));
		set_film_aspect_ratio(0.0f);
		set_focal_length(0.0f);
		set_aspect_ratio(0.0f);
		set_znear(0.0f);
		set_zfar(0.0f);
		this->fovy_ = 0.0f;
		this->ortho_left_ = 0.0f;
		this->ortho_right_ = 0.0f;
		this->ortho_bottom_ = 0.0f;
		this->ortho_top_ = 0.0f;
	}
	/*
		Move camera at position \param pos and set target \param target
	*/
	void FCamera::LookAt(const FPoint3f& pos, const FPoint3f& target, const FPoint3f& up)
	{
		this->SetTransition(pos);
		this->upVector = up;
		LookAt(target);	
	}

	void FCamera::LookAt(const FPoint3f & target)
	{
		this->target_point_ = target;
		auto position = this->GetTransition();
		auto zaxis = (position - target_point_).normalized();
		auto xaxis = (upVector.cross(zaxis)).normalized();
		auto yaxis = zaxis.cross(xaxis);
		this->view_ = Eigen::MatrixXf::Zero(4, 4);
		FMatrix3f m;
		m.col(0) = zaxis;
		m.col(1) = xaxis;
		m.col(2) = yaxis;
		this->view_.topLeftCorner(3, 3) = m;
		this->view_.col(3) = FPoint4f( 0.0f, 0.0f, 0.0f, 1.0f);
		this->view_(3, 0) = -xaxis.dot(position);
		this->view_(3, 1) = -yaxis.dot(position);
		this->view_(3, 2) = -zaxis.dot(position);
		this->view_(3, 3) = 1.0f;
	}

	void FCamera::SetPerspective(const FAngle& fovy, float aspect, float z_near, float z_far)
	{
		set_fovy(fovy);
		set_aspect_ratio(aspect);
		set_znear(z_near);
		set_zfar(z_far);
		UpdatePerspective();
	}

	void FCamera::UpdatePerspective()
	{
		auto range = zfar_ - znear_;
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

	void FCamera::SetOrtho(float left, float right, float bottom, float top)
	{
		this->ortho_left_ = left;
		this->ortho_right_ = right;
		this->ortho_bottom_ = bottom;
		this->ortho_top_ = top;
		UpdateOrtho();
	}

	void FCamera::UpdateOrtho()
	{
		this->projection_ = Eigen::MatrixXf::Zero(4, 4);

		projection_(0, 0) = 2.0f / (this->ortho_right_ - this->ortho_left_);
		projection_(1, 1) = 2.0f / (this->ortho_top_ - this->ortho_bottom_);
		projection_(2, 2) = -2.0f / (zfar_ - znear_);
		projection_(3, 0) = -(this->ortho_right_ + this->ortho_left_) / (this->ortho_right_ - this->ortho_left_);
		projection_(3, 1) = -(this->ortho_top_ + this->ortho_bottom_) / (this->ortho_top_ - this->ortho_bottom_);
		// TODO: IS IT NEEDED TO USE zfar and znear IN orth projection?? 
		projection_(3, 2) = -(zfar_ + znear_) / (zfar_ - znear_);
		projection_(3, 3) = 1.0f;

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
	}

	void FCamera::set_zfar(float zfar)
	{
		this->zfar_ = zfar;
	}

	void FCamera::set_fovy(const FAngle & angle)
	{
		this->fovy_ = angle.radians();
	}

	void FCamera::set_aspect_ratio(float aspect_ratio)
	{
		this->aspect_ratio_ = aspect_ratio_;
	}

	void FCamera::set_target(const FPoint3f & target)
	{
		this->target_point_ = target;
	}

	void FCamera::set_target(FShared<FEntity> target)
	{
		this->target_entity_ = target;
		this->target_point_ = target != nullptr ? target->GetTransition() : FPoint3f(0.0f, 0.0f, 0.0f);
	}

	void FCamera::updateViewProjectionMatrix()
	{
		this->view_projection_ = view_ * projection_;
	}
}