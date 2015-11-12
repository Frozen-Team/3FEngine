#ifndef _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_
#define _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_

#include <utils/f_typedefs.hpp>
#include <scene/entity/f_entity.hpp>
#include <utils/f_angle.hpp>

namespace fengine {
	class FCamera : public FEntity
	{
	public:
		FCamera();
		FCamera(uint64_t id, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale, const FPoint3f& targ, const FPoint2f& aperture_,
			float film_aspect_ratio, float focal_length, float aspect_ratio, float znear, float zfar, const FAngle& fovy);
		void LookAt(const FPoint3f& target);
		void UpdatePerspective();
		void UpdateOrtho(float left, float right, float bottom, float top);

		void set_aperture(const FPoint2f& apperture);
		void set_aperture(float width, float height);
		void set_film_aspect_ratio(float film_aspect_ration);
		void set_focal_length(float focal_length);
		void set_znear(float znear);
		void set_zfar(float zfar);
		void set_fovy(const FAngle& angle);

		FMatrix4f& view_projection() noexcept { return view_projection_; }
		FMatrix4f& view() noexcept { return view_; }
		FMatrix4f& projection() noexcept { return projection_; }
		FPoint2f& aperture() noexcept { return aperture_; }
		float film_aspect_ratio() const noexcept { return film_aspect_ratio_; }

	private:
		void updateViewProjectionMatrix();

	public:
		const static FPoint3f kUpVector; 

	private:
		FMatrix4f view_;
		FMatrix4f projection_;
		FMatrix4f view_projection_;

		FPoint3f target_;
		FPoint2f aperture_; // in meters

		float film_aspect_ratio_;
		float focal_length_;
		float aspect_ratio_;
		float znear_;
		float zfar_;
		float fovy_; // in radians
		
	};
}
#endif // _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_