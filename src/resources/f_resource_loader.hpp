#ifndef _3FENGINE_SRC_RESOURCES_F_RESOURCE_LOADER_HPP
#define _3FENGINE_SRC_RESOURCES_F_RESOURCE_LOADER_HPP

#include "fbxsdk.h"

#include "fcomponents/f_logger.hpp"
#include "utils/f_typedefs.hpp"
#include "fbx2fseq/Core/f_fbx_loader.hpp"
#include "utils/f_singleton.hpp"
#include "scene/camera/f_camera.hpp"
#include "scene/f_scene.hpp"
#include "scene/mesh/f_mesh.hpp"
#include "scene/mesh/f_mesh_lod.hpp"

/*
	Raw pointers here are used only because of fbxsdk
	Unnecessary to wrap raw pointers into smart pointers for now
*/
namespace fengine {
	class FResourceLoader : public FFbxLoader, public futils::FSingleton<FResourceLoader> {
		F_DISABLE_COPY(FResourceLoader)
		
	public:
		F_DEFAULT_CTOR_V_DTOR(FResourceLoader)

		FShared<FScene> ImportScene(const std::string& fbx_file);
		void LoadComponent(FShared<FScene>& scene, FbxNode* node);
		FShared<FMesh> LoadMesh(FbxNode* node);
		FShared<FMesh> LoadLodGroup(FbxNode* node);
		FMeshLod& LoadLod(FbxNode* node, float threshold);
		FShared<FCamera> LoadCamera(FbxNode* node);
		FUvsf LoadUvs(FbxMesh* mesh);
	private:

	};
}
#endif // _3FENGINE_SRC_RESOURCES_F_RESOURCE_LOADER_HPP