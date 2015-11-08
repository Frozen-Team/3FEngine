#ifndef _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_
#define _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_

#include "utils/f_typedefs.hpp"
#include "scene/f_scene_node.hpp"

namespace fengine {
	class FCamera : public FSceneNode 
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FCamera)

		FCamera(const FPoint3f& pos, const FPoint3f& targ);
		void LookAt(const FPoint3f& target);
		void UpdatePerspective();
		void UpdateOrtho(float left, float right, float bottom, float top, float zNear, float zFar);

		void set_aperture(const FPoint2f& apperture);
		void set_aperture(float width, float height);
		void set_film_aspect_ratio(float film_aspect_ration);
		void set_focal_length(float focal_length);
		void set_znear(float znear);
		void set_zfar(float zfar);
		void set_fovy_d(float degrees);
		void set_fovy_r(float radians);

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

		FPoint3f position_;
		FPoint3f target_;
		FPoint2f aperture_; // in mm

		float film_aspect_ratio_;
		float focal_length_;
		float aspect_ratio_;
		float znear_;
		float zfar_;
		float fovy_; // in radians
		
	};
}
#endif // _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_