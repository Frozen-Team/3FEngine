#include "f_camera.hpp"
#include "utils/f_utils.hpp"

namespace fengine{
	const FPoint3f FCamera::kUpVector = { 0.0f, 1.0f, 0.0f };
	
	FCamera::FCamera() : target_(0, 0, 0), aperture_(0, 0), film_aspect_ratio_(0), focal_length_(0), 
		aspect_ratio_(0), znear_(0), zfar_(0), fovy_(0)
	{
	}

	FCamera::FCamera(const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale, const FPoint3f& targ, const FPoint2f& aperture_,
		float film_aspect_ratio, float focal_length, float aspect_ratio, float znear, float zfar, const FAngle& fovy)
		: FTransformationMatrix(transition, rotation, scale), aperture_(aperture_), film_aspect_ratio_(film_aspect_ratio), focal_length_(focal_length),
		aspect_ratio_(aspect_ratio), znear_(znear), zfar_(zfar)
	{
		this->set_fovy(fovy);
		this->LookAt(targ);
		this->UpdatePerspective();
	}

	void FCamera::LookAt(const FPoint3f & target)
	{
		this->target_ = target;
		auto position = this->GetTransition();
		auto zaxis = (position - target_).normalized();
		auto xaxis = (kUpVector.cross(zaxis)).normalized();
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


	void FCamera::updateViewProjectionMatrix()
	{
		this->view_projection_ = view_ * projection_;
	}
}