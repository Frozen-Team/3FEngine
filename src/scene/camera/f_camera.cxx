#include "f_camera.hpp"

namespace fengine{
	const FPoint3f FCamera::kUpVector = { 0.0f, 1.0f, 0.0f };

	FCamera::FCamera(const FPoint3f & pos, const FPoint3f & targ) : position_(pos) 
	{
		this->LookAt(targ);
	}

	void FCamera::LookAt(const FPoint3f & target)
	{
		this->target_ = target;

		auto zaxis = (position_ - target_).normalized();
		auto xaxis = (kUpVector.cross(zaxis)).normalized();
		auto yaxis = zaxis.cross(xaxis);
		this->view_ = Eigen::MatrixXf::Zero(4, 4);
		FMatrix3f m;
		m.col(0) = zaxis;
		m.col(1) = xaxis;
		m.col(2) = yaxis;
		this->view_.topLeftCorner(3, 3) = m;
		this->view_.col(3) = FPoint4f( 0.0f, 0.0f, 0.0f, 1.0f);
		this->view_(3, 0) = -xaxis.dot(position_);
		this->view_(3, 1) = -yaxis.dot(position_);
		this->view_(3, 2) = -zaxis.dot(position_);
		this->view_(3, 3) = 1.0f;
	}

	void FCamera::SetPerspective(float fovY, float aspectRatio, float zNear, float zFar)
	{
		auto range = zFar - zNear;
		auto invtan = 1.0f / tan(fovY * 0.5f);
		this->projection_ = Eigen::MatrixXf::Zero(4, 4);

		projection_(0, 0) = invtan / aspectRatio;
		projection_(1, 1) = invtan;
		projection_(2, 2) = -(zNear + zFar) / range;
		projection_(3, 2) = -1;
		projection_(2, 3) = -2 * zNear * zFar / range;
		projection_(3, 3) = 0;

		updateViewProjectionMatrix();
	}

	void FCamera::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		this->projection_ = Eigen::MatrixXf::Zero(4, 4);

		projection_(0, 0) = 2.0f / (right - left);
		projection_(1, 1) = 2.0f / (top - bottom);
		projection_(2, 2) = -2.0f / (zFar - zNear);
		projection_(3, 0) = -(right + left) / (right - left);
		projection_(3, 1) = -(top + bottom) / (top - bottom);
		projection_(3, 2) = -(zFar + zNear) / (zFar - zNear);
		projection_(3, 3) = 1.0f;

		updateViewProjectionMatrix();
	}

	void FCamera::set_aperture(const FPoint2f& apperture)
	{ this->aperture_ = apperture; }

	void FCamera::set_aperture(float width, float height)
	{
		this->aperture_[0] = width;
		this->aperture_[1] = height;
	}

	void FCamera::set_film_aspect_ratio(float film_aspect_ratio)
	{
		this->film_aspect_ratio_ = film_aspect_ratio;
		this->set_aperture(film_aspect_ratio * 50, this->aperture()[1]);
	}

	void FCamera::updateViewProjectionMatrix()
	{
		this->view_projection_ = view_ * projection_;
	}
}