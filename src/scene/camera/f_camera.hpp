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
		void SetPerspective(float fovY, float aspectRatio, float zNear, float zFar);
		void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
		void set_aperture(const FPoint2f& apperture);
		void set_aperture(float width, float height);
		void set_film_aspect_ratio(float film_aspect_ration);

		FMatrix4f& view_projection() noexcept { return view_projection_; }
		FMatrix4f& view() noexcept { return view_; }
		FMatrix4f& projection() noexcept { return projection_; }
		FPoint2f& aperture() noexcept { return aperture_; }
		
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
	};
}
#endif // _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_