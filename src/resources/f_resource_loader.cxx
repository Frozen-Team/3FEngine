#include "f_resource_loader.hpp"
#include "resources/components_loader/fbx_mesh_loader.hpp"
#include "resources/components_loader/fbx_lod_group_loader.hpp"
#include "components_loader/fbx_camera_loader.hpp"
#include <utils/f_angle.hpp>
#include "fcomponents/f_logger.hpp"

namespace fengine {
	FShared<FScene> FResourceLoader::ImportScene(const std::string& fbx_file)
	{
		auto res_scene = std::make_shared<FScene>();

		LOG_IF(!this->LoadScene(fbx_file), FATAL) << "Failed to import the scene from file: " << fbx_file;

		auto root_node = this->fbx_scene()->GetRootNode();
		LOG_IF(!root_node, FATAL) << "Failed to retrieve a root node";

		auto root_node_ch_count = root_node->GetChildCount();
		for (auto i = 0; i < root_node_ch_count; i++)
		{
			//as we import from root node, we haven't had a parent yet
			this->LoadComponent(res_scene, nullptr, root_node->GetChild(i));
		}

		return res_scene;
	}


	void FResourceLoader::LoadComponent(FShared<FScene>& scene, FShared<FEntity> parent, FbxNode * node) const
	{
		LOG_IF(!node, FATAL) << "Passed invalid scene";
		auto node_attr = node->GetNodeAttribute();
		FShared<FEntity> current = nullptr;
		if (node_attr)
		{
			auto node_type = node_attr->GetAttributeType();
			switch (node_type)
			{
			case FbxNodeAttribute::eMesh:
			{
				auto mesh = this->LoadMesh(node);
				scene->Add(mesh);
				current = std::static_pointer_cast<FEntity>(mesh);
				break;
			}
			//TODO: LOD group need to be reconsidered
			case FbxNodeAttribute::eLODGroup:
			{
				auto lod_group_mesh = this->LoadLodGroup(node);
				scene->Add(lod_group_mesh);
				current = std::static_pointer_cast<FEntity>(lod_group_mesh);
				return; // workaround for now
			}		
			case FbxNodeAttribute::eCamera:
			{
				auto camera = this->LoadCamera(node);
				scene->Add(camera);
				current = std::static_pointer_cast<FEntity>(camera);
				break;
			}
				
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
		if (parent)
		{
			current->set_parent(parent);
			parent->AddChild(current);
		}
		auto node_ch_count = node->GetChildCount();
		for (auto i = 0; i < node_ch_count; i++)
		{
			this->LoadComponent(scene, current, node->GetChild(i));
		}

	}

	FShared<FMesh> FResourceLoader::LoadMesh(FbxNode *node) const
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadMesh";
		auto mesh = std::make_shared<FMesh>(
			LoadUniqueId(node),
			LoadTransition(node),
			LoadRotation(node),
			LoadScale(node)
		);
		mesh->AddLod(this->LoadLod(node, FLT_MAX));
		return mesh;
	}

	uint64_t FResourceLoader::LoadUniqueId(FbxNode* node)
	{
		return static_cast<uint64_t>(node->GetUniqueID());
	}

	FShared<FMesh> FResourceLoader::LoadLodGroup(FbxNode * node) const
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadLodGroup";
		
		auto node_ch_count = node->GetChildCount();
		auto fbx_lod_group = static_cast<FbxLodGroupLoader*>(node->GetNodeAttribute());
		FVector<FMeshLod> lods;
		lods.reserve(node_ch_count);
		for (auto i = 0; i < node_ch_count; i++)
		{
			auto threshold = fbx_lod_group->RetrieveThreshold(i);
			lods.push_back(this->LoadLod(node, threshold));
		}
		auto mesh = std::make_shared<FMesh>(
				LoadUniqueId(node), // id of lod group
				LoadTransition(node),
				LoadRotation(node),
				LoadScale(node)
			);
		mesh->AddLods(lods);
		return mesh;
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

	FShared<FCamera> FResourceLoader::LoadCamera(FbxNode * node) const
	{
		LOG_IF(!node, FATAL) << "Invalid node passed to LoadCamera";

		auto fbx_camera = static_cast<FbxCameraLoader*>(node->GetNodeAttribute());

		return std::make_shared<FCamera>(
			LoadUniqueId(node),
			LoadTransition(node),
			LoadRotation(node),
			LoadScale(node),
			fbx_camera->GetTarget(),
			fbx_camera->GetApperture(),
			static_cast<float>(fbx_camera->FilmAspectRatio.Get()),
			static_cast<float>(fbx_camera->FocalLength.Get()),
			0.0f,//TODO: get aspect ratio
			static_cast<float>(fbx_camera->NearPlane.Get()),
			static_cast<float>(fbx_camera->FarPlane.Get()),
			FAngle::Degrees(static_cast<float>(fbx_camera->FieldOfViewY.Get()))
			);;
	}

	FPoint3f FResourceLoader::LoadTransition(FbxNode * node)
	{
		auto position = node->LclTranslation.Get();
		return ToPoint3f(position);
	}

	FPoint3f FResourceLoader::LoadRotation(FbxNode* node)
	{
		auto rotation = node->LclRotation.Get();
		return ToPoint3f(rotation);
	}

	FPoint3f FResourceLoader::LoadScale(FbxNode* node)
	{
		auto scale = node->LclScaling.Get();
		return ToPoint3f(scale);
	}
}
