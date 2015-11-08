#include "fbx_camera_loader.hpp"

namespace fengine
{
	FPoint3f FbxCameraLoader::GetTarget(const FbxTime& time) const
	{
		auto lookAt = this->EvaluateLookAtPosition(time);
		return FPoint3f(
			static_cast<float>(lookAt.mData[0]),
			static_cast<float>(lookAt.mData[1]),
			static_cast<float>(lookAt.mData[2])
			);
	}
}
