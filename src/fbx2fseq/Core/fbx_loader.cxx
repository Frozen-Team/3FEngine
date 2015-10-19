#include "fbx_loader.hpp"

FbxManager* FFbxLoader::fbx_manager_ = nullptr;
FbxIOSettings* FFbxLoader::fbx_io_settings_ = nullptr;
FbxImporter* FFbxLoader::fbx_importer_ = nullptr;

FFbxLoader::FFbxLoader() {
	fbx_manager_ = FbxManager::Create();
	if (fbx_manager_ == nullptr) { LOG(FATAL) << "Fbx manager failed to initialize"; }
	//TODO: be careful here with IOSN_IMPORT. Need tests
	fbx_io_settings_ = FbxIOSettings::Create(fbx_manager_, IOSN_IMPORT);
	if (fbx_io_settings_ == nullptr) { LOG(FATAL) << "Fbx io settings failed to initialize"; }
	fbx_manager_->SetIOSettings(fbx_io_settings_);
	assert(fbx_manager_ && fbx_io_settings_);
	fbx_importer_ = FbxImporter::Create(fbx_manager_, "");
}
