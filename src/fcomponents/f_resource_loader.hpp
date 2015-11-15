#ifndef _3FENGINE_SRC_RESOURCES_F_RESOURCE_LOADER_HPP
#define _3FENGINE_SRC_RESOURCES_F_RESOURCE_LOADER_HPP

#include "fbxsdk.h"


#include "utils/f_typedefs.hpp"
#include "resources/f_fbx_loader.hpp"
#include "utils/f_singleton.hpp"
#include "scene/camera/f_camera.hpp"
#include "scene/f_scene.hpp"
#include "scene/mesh/f_mesh.hpp"
#include "scene/mesh/f_mesh_lod.hpp"
#include "scene/entity/f_entity.hpp"

/*
	Raw pointers here are used only because of fbxsdk
	Unnecessary to wrap raw pointers into smart pointers for now
*/
namespace fengine {
	class FResourceLoader : public FFbxLoader, private futils::FSingleton<FResourceLoader> 
	{
		friend class Engine;
		F_DISABLE_COPY(FResourceLoader)

	public:
		F_DEFAULT_CTOR_V_DTOR(FResourceLoader)

		/**
			Import a scene data from a specified file to a specified FShared<FScene> object. If the object doesn't specified(or specified with nullptr)
			a new scene is created.

			\param[in]	fbx_file filepath to an fbx file, where a scene is stored
			\param[out]	scene Scene where a content of fbx_file will be stored. By default it's nullptr, so a new scene is created.
			\return shared pointer to FScene, where the content of the fbx_file is stored.
		*/
		static FShared<FScene> LoadScene(const FString& fbx_file, FShared<FScene> scene=nullptr);


	private:
		static void LoadComponent(FShared<FScene>& scene, FShared<FEntity> parent, FbxNode* node);

		static FMeshLod LoadLod(FbxNode* node, float threshold);
		static FShared<FMesh> LoadLodGroup(FbxNode* node);
		static FShared<FCamera> LoadCamera(FbxNode* node, FShared<FScene>& scene);
		static FShared<FMesh> LoadMesh(FbxNode* node);

		static uint64_t LoadUniqueId(FbxNode* node);
		static FString	LoadName(FbxNode* node);
		static FPoint3f LoadTransition(FbxNode* node);
		static FPoint3f LoadRotation(FbxNode* node);
		static FPoint3f LoadScale(FbxNode* node);

		template<class T>
		static FShared<T> LoadEntityBase(FbxNode* base_node)
		{
			return std::make_shared<T>(
				LoadUniqueId(base_node),
				LoadName(base_node),
				LoadTransition(base_node),
				LoadRotation(base_node),
				LoadScale(base_node)
			);
		}
		//pass an array which has at least 3 elements
		template<typename T>
		static FPoint3f ToPoint3f(T fbxData)
		{
			return FPoint3f(
				static_cast<float>(fbxData[0]),
				static_cast<float>(fbxData[1]),
				static_cast<float>(fbxData[2])
				);
		}
	};
}
#endif // _3FENGINE_SRC_RESOURCES_F_RESOURCE_LOADER_HPP