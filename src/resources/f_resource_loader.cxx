#include "f_resource_loader.hpp"
#include "resources/components_loader/fbx_mesh_loader.hpp"

namespace fengine {
	FShared<FScene> FResourceLoader::ImportScene(const std::string& fbx_file)
	{
		auto res_scene = std::make_shared<FScene>();

		LOG_IF(!this->LoadScene(fbx_file), FATAL) << "Failed to import the scene from file: " << fbx_file;

		auto root_node = this->fbx_scene()->GetRootNode();
		LOG_IF(!root_node, FATAL) << "Failed to retrieve a root node";

		auto root_node_ch_count = root_node->GetChildCount();
		for (int i = 0; i < root_node_ch_count; i++)
		{
			this->LoadComponent(res_scene, root_node->GetChild(i));
		}

		return res_scene;
	}
	void FResourceLoader::LoadComponent(FShared<FScene>& scene, FbxNode * node)
	{
		LOG_IF(!node, FATAL) << "Passed invalid scene";
		auto node_attr = node->GetNodeAttribute();
		if (node_attr)
		{
			auto k_node_type = node_attr->GetAttributeType();
			switch (k_node_type)
			{
			case FbxNodeAttribute::eMesh:
			{
				scene->Add(this->LoadMesh(node));
				break;
			}
			case FbxNodeAttribute::eLODGroup:
				scene->Add(this->LoadLodGroup(node));
				break;
			case FbxNodeAttribute::eCamera:
				scene->Add(this->LoadCamera(node));
				break;
			case FbxNodeAttribute::eUnknown: break;
			case FbxNodeAttribute::eNull: break;
			case FbxNodeAttribute::eMarker: break;
			case FbxNodeAttribute::eSkeleton: break;
			case FbxNodeAttribute::eNurbs: break;
			case FbxNodeAttribute::ePatch: break;
			case FbxNodeAttribute::eCameraStereo: break;
			case FbxNodeAttribute::eCameraSwitcher: break;
			case FbxNodeAttribute::eLight: break;
			case FbxNodeAttribute::eOpticalReference: break;
			case FbxNodeAttribute::eOpticalMarker: break;
			case FbxNodeAttribute::eNurbsCurve: break;
			case FbxNodeAttribute::eTrimNurbsSurface: break;
			case FbxNodeAttribute::eBoundary: break;
			case FbxNodeAttribute::eNurbsSurface: break;
			case FbxNodeAttribute::eShape: break;
			case FbxNodeAttribute::eSubDiv: break;
			case FbxNodeAttribute::eCachedEffect: break;
			case FbxNodeAttribute::eLine: break;
			default: break;
			}
		}
	}

	FShared<FMesh> FResourceLoader::LoadMesh(FbxNode *node) const
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadMesh";
		auto mesh = std::make_shared<FMesh>();
		mesh->AddLod(this->LoadLod(node, FLT_MAX));
		mesh->set_position(this->LoadPosition(node));
		return mesh;
	}

	FShared<FMesh> FResourceLoader::LoadLodGroup(FbxNode * node)
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadLodGroup";
		return FShared<FMesh>();
	}

	FMeshLod FResourceLoader::LoadLod(FbxNode * node, float threshold) const
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadLod";
		auto fbx_mesh = static_cast<FbxMeshLoader*>(node->GetNodeAttribute());
		return FMeshLod(threshold, std::make_shared<FGeometry>(
			fbx_mesh->LoadIndices(),
			fbx_mesh->LoadVertices(),
			fbx_mesh->LoadUvs()));
	}

	FShared<FCamera> FResourceLoader::LoadCamera(FbxNode * node)
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadCamera";
		return FShared<FCamera>();
	}

	FPoint3f FResourceLoader::LoadPosition(FbxNode * node)
	{
		auto position = node->LclTranslation.Get();
		return FPoint3f(
			static_cast<float>(position[0]), 
			static_cast<float>(position[1]), 
			static_cast<float>(position[2])
			);
	}
}