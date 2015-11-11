#ifndef FBX2FSEQ_SRC_CORE_FBX_LOADER_HPP_
#define FBX2FSEQ_SRC_CORE_FBX_LOADER_HPP_

#include <string>
#include <memory>

#include "fbxsdk.h"
#include "fbxsdk/fileio/fbxiosettings.h"

#include "utils/f_typedefs.hpp"
#include "fcomponents/f_logger.hpp"
#include "resources/components_loader/fbx_scene_loader.hpp"

class FFbxLoader 
{
	F_DISABLE_COPY(FFbxLoader)
public:
	FFbxLoader();
	virtual ~FFbxLoader() = default;

	bool LoadScene(const std::string& filepath);
public:
	static FbxManager* fbx_manager() { return fbx_manager_; }
	static FbxIOSettings* fbx_io_settings() { return fbx_io_settings_; }
	static FbxImporter* fbx_importer() { return fbx_importer_; }
	FbxSceneLoader* fbx_scene() const { return fbx_scene_; }
private:

private:
	static FbxManager* fbx_manager_;
	static FbxIOSettings* fbx_io_settings_;
	static FbxImporter* fbx_importer_;
	FbxSceneLoader* fbx_scene_;
};
#endif // FBX2FSEQ_SRC_CORE_FBX_LOADER_HPP_
