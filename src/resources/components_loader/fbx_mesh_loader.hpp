#ifndef FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_MESH_LOADER_HPP_
#define FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_MESH_LOADER_HPP_

#include"fbxsdk.h"

#include "fcomponents/f_logger.hpp"
#include "utils/f_typedefs.hpp"

namespace fengine 
{
	class FbxMeshLoader : public FbxMesh 
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FbxMeshLoader)

		FVertices3f LoadVertices() const;
		FIndices3 LoadIndices() const;
		FUvsf LoadUvs();
	};
}


#endif // FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_MESH_LOADER_HPP_