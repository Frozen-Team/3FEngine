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

		FMatrix4f& view_projection() noexcept { return view_projection_; }
		FMatrix4f& view() noexcept { return view_; }
		FMatrix4f& projection() noexcept { return projection_; }

	private:
		void updateViewProjectionMatrix();

	public:
		const static FPoint3f kUpVector; 

	private:
		FPoint3f position_;
		FPoint3f target_;
		FMatrix4f view_;
		FMatrix4f projection_;
		FMatrix4f view_projection_;
	};
}
#endif // _3FENGINE_SRC_SCENE_CAMERA_F_CAMERA_HPP_