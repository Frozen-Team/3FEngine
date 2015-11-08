#include "fbx_camera_loader.hpp"

namespace fengine
{
	FPoint3f FbxCameraLoader::GetTarget(const FbxTime& time) const
	{
		auto lookAt = this->EvaluateLookAtPosition(time);
		auto a = this->FieldOfViewY.Get();
		return FPoint3f(
			static_cast<float>(lookAt.mData[0]),
			static_cast<float>(lookAt.mData[1]),
			static_cast<float>(lookAt.mData[2])
			);
	}

	FPoint2f FbxCameraLoader::GetApperture() const
	{
		return FPoint2f(
			static_cast<float>(this->GetApertureWidth() * 25.4),
			static_cast<float>(this->GetApertureHeight() * 25.4)
			);
	}
}
