#ifndef FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_CAMERA_LOADER_HPP_
#define FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_CAMERA_LOADER_HPP_

#include "fbxsdk.h"
#include "utils/f_typedefs.hpp"

namespace fengine
{
	class FbxCameraLoader : public FbxCamera
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FbxCameraLoader)

		FPoint3f GetTarget(const FbxTime & 	pTime = FBXSDK_TIME_ZERO) const;
		FPoint2f GetApperture() const;
	};
}

#endif //FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_CAMERA_LOADER_HPP_