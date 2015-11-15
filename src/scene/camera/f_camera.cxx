#include "f_camera.hpp"
#include "utils/f_utils.hpp"

namespace fengine{
	const FPoint3f FCamera::kUpVector = { 0.0f, 1.0f, 0.0f };
	
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
		LookAt(nullptr);
		set_aperture(FPoint2f(0.0f, 0.0f));
		set_film_aspect_ratio(0.0f);
		set_focal_length(0.0f);
		set_aspect_ratio(0.0f);
		set_znear(0.0f);
		set_zfar(0.0f);
		this->fovy_ = 0.0f;
	}

	void FCamera::LookAt(const FPoint3f & target)
	{
		this->target_point_ = target;
		UpdateViewMatrix();
	}

	void FCamera::LookAt(FShared<FEntity> target)
	{
		this->target_entity_ = target;
		this->target_point_ = target != nullptr ? target->GetTransition() : FPoint3f(0.0f, 0.0f, 0.0f);
		UpdateViewMatrix();
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

	void FCamera::UpdateOrtho(float left, float right, float bottom, float top)
	{
		this->projection_ = Eigen::MatrixXf::Zero(4, 4);

		projection_(0, 0) = 2.0f / (right - left);
		projection_(1, 1) = 2.0f / (top - bottom);
		projection_(2, 2) = -2.0f / (zfar_ - znear_);
		projection_(3, 0) = -(right + left) / (right - left);
		projection_(3, 1) = -(top + bottom) / (top - bottom);
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

	void FCamera::updateViewProjectionMatrix()
	{
		this->view_projection_ = view_ * projection_;
	}

	void FCamera::UpdateViewMatrix()
	{
		auto position = this->GetTransition();
		auto zaxis = (position - target_point_).normalized();
		auto xaxis = (kUpVector.cross(zaxis)).normalized();
		auto yaxis = zaxis.cross(xaxis);
		this->view_ = Eigen::MatrixXf::Zero(4, 4);
		FMatrix3f m;
		m.col(0) = zaxis;
		m.col(1) = xaxis;
		m.col(2) = yaxis;
		this->view_.topLeftCorner(3, 3) = m;
		this->view_.col(3) = FPoint4f(0.0f, 0.0f, 0.0f, 1.0f);
		this->view_(3, 0) = -xaxis.dot(position);
		this->view_(3, 1) = -yaxis.dot(position);
		this->view_(3, 2) = -zaxis.dot(position);
		this->view_(3, 3) = 1.0f;
	}
}
