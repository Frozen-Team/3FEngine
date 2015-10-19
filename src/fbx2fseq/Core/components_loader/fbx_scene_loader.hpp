#ifndef FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_SCENE_LOADER_HPP_
#define FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_SCENE_LOADER_HPP_

#include "fbxsdk.h"
#include "../fbx_loader.hpp"

class FbxSceneLoader : public FbxScene {
private:
public:
	inline bool Load(const std::string& filepath) {
		assert(FFbxLoader::fbx_importer() && FFbxLoader::fbx_io_settings());
		if (!FFbxLoader::fbx_importer()->Initialize(filepath.c_str(), -1, FFbxLoader::fbx_io_settings())) {
			LOG(FATAL) << "Failed to initialize fbx importer";
		}
		auto fbx_scene = dynamic_cast<FbxSceneLoader*>(Create(FFbxLoader::fbx_manager(), "importedScene"));
		if (!fbx_scene) { return false; }	
		return FFbxLoader::fbx_importer()->Import(fbx_scene);
	}
};

#endif // FBX2FSEQ_SRC_CORE_COMPONENTS_LOADER_FBX_SCENE_LOADER_HPP_