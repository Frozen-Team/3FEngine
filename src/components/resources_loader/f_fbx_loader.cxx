#include "f_resources_loader.hpp"


namespace fengine {
	FFbxLoader::FFbxLoader() : fbx_manager_(nullptr), fbx_io_settings_(nullptr), fbx_importer_(nullptr) {
		fbx_manager_ = FbxManager::Create();
		if (fbx_manager_ == nullptr) { LOG(FATAL) << "Fbx manager failed to initialize"; }
		//TODO: be careful here with IOSN_IMPORT. Need tests
		fbx_io_settings_ = FbxIOSettings::Create(fbx_manager_, IOSN_IMPORT);
		if (fbx_io_settings_ == nullptr) { LOG(FATAL) << "Fbx io settings failed to initialize"; }
		fbx_manager_->SetIOSettings(fbx_io_settings_);
	}
}
