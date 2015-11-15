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
		explicit FCamera(uint64_t id, const FString& name, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale);

		void ResetSecondaryAttrToDefault();
		void LookAt(const FPoint3f& target);
		void LookAt(FShared<FEntity> target);
		void UpdatePerspective();
		void UpdateOrtho(float left, float right, float bottom, float top);

		void set_aperture(const FPoint2f& apperture);
		void set_aperture(float width, float height);
		void set_film_aspect_ratio(float film_aspect_ration);
		void set_focal_length(float focal_length);
		void set_znear(float znear);
		void set_zfar(float zfar);
		void set_fovy(const FAngle& angle);
		void set_aspect_ratio(float aspect_ratio);

		FMatrix4f& view_projection() noexcept { return view_projection_; }
		FMatrix4f& view() noexcept { return view_; }
		FMatrix4f& projection() noexcept { return projection_; }
		FPoint2f& aperture() noexcept { return aperture_; }
		float film_aspect_ratio() const noexcept { return film_aspect_ratio_; }

	private:
		void updateViewProjectionMatrix();
		void UpdateViewMatrix();

	public:
		const static FPoint3f kUpVector; 

	private:
		FMatrix4f view_;
		FMatrix4f projection_;
		FMatrix4f view_projection_;

		// if the camera has aim, bind an aimed entity to target_entity_ field
		// in this case target_point_ will be set to a transition value of the target_entity_
		FShared<FEntity> target_entity_;
		
		// if its an ordinar camera, target_entity_ is set to nullptr, and target_point_ to a certain position
		FPoint3f target_point_;
		
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