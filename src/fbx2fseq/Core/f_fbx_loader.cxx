#include "f_fbx_loader.hpp"


FbxManager* FFbxLoader::fbx_manager_ = nullptr;
FbxIOSettings* FFbxLoader::fbx_io_settings_ = nullptr;
FbxImporter* FFbxLoader::fbx_importer_ = nullptr;

FFbxLoader::FFbxLoader() {
	fbx_manager_ = FbxManager::Create();
	LOG_IF(fbx_manager_ == nullptr, FATAL) << "Fbx manager failed to initialize";
	//TODO: be careful here with IOSN_IMPORT. Need tests
	fbx_io_settings_ = FbxIOSettings::Create(fbx_manager_, IOSN_IMPORT);
	LOG_IF(fbx_io_settings_ == nullptr, FATAL) << "Fbx io settings failed to initialize";

	fbx_manager_->SetIOSettings(fbx_io_settings_);
	assert(fbx_manager_ && fbx_io_settings_);
	fbx_importer_ = FbxImporter::Create(fbx_manager_, "");
}


bool FFbxLoader::LoadScene(const std::string& filepath)
{
	LOG_IF(!FFbxLoader::fbx_importer(), FATAL) << "Importer isn't created";
	LOG_IF(!FFbxLoader::fbx_io_settings(), FATAL) << "Settings aren't initialized";

	if (!FFbxLoader::fbx_importer()->Initialize(filepath.c_str(), -1, FFbxLoader::fbx_io_settings())) {
		LOG(FATAL) << "Failed to initialize fbx importer";
	}

	//TODO: is it efficient to recreate scene here?
	fbx_scene_ = dynamic_cast<FbxSceneLoader*>(FbxSceneLoader::Create(FFbxLoader::fbx_manager(), "importedScene"));
	if (!fbx_scene_) { 
		LOG(ERROR) << "Fbx scene from file " << filepath << " failed to be created";
		return false; 
	}
	return FFbxLoader::fbx_importer()->Import(fbx_scene_);
}
