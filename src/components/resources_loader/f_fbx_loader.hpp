#ifndef _3FENGINE_SRC_COMPONENTS_F_FBX_LOADER_HPP_
#define _3FENGINE_SRC_COMPONENTS_F_FBX_LOADER_HPP_

#include "fbxsdk.h"
#include "fbxsdk/fileio/fbxiosettings.h"
#include <string>
#include <memory>

#include "../../utils/f_typedefs.hpp"
#include "../../utils/f_singleton.hpp"
#include "../f_logger.hpp"

namespace fengine {
	class FFbxLoader : public futils::FSingleton<FFbxLoader>
	{
		F_DISABLE_COPY(FFbxLoader)
	public:
		~FFbxLoader() = default;
		FFbxLoader(); 

	private:
		//static FVertices3f LoadVertices();
		inline bool LoadScene(const std::string& filename, FbxScene* fbx_scene) {
			assert(fbx_manager_ && fbx_io_settings_);
			fbx_importer_ = FbxImporter::Create(fbx_manager_, "");
			auto import_status = fbx_importer_->Initialize(filename.c_str(), -1, fbx_io_settings_);

			if (!import_status) {
				LOG(FATAL) << "Failed to initialize fbx importer";
			}

			fbx_scene = FbxScene::Create(fbx_manager_, "importedScene");
			return fbx_importer_->Import(fbx_scene);
		}
		
	private:
		FbxManager* fbx_manager_;
		FbxIOSettings* fbx_io_settings_;
		FbxImporter* fbx_importer_;
	};
}

#endif // _3FENGINE_SRC_COMPONENTS_F_FBX_LOADER_HPP_
