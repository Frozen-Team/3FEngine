#include "f_resource_loader.hpp"

#include <fcomponents/f_logger.hpp>
#include <utils/f_angle.hpp>

#include <resources/components_loader/fbx_mesh_loader.hpp>
#include <resources/components_loader/fbx_lod_group_loader.hpp>
#include <resources/components_loader/fbx_camera_loader.hpp>

namespace fengine {
	
	FShared<FScene> FResourceLoader::LoadScene(const FString& fbx_file, FShared<FScene> scene )
	{
		if (!scene)
		{
			scene = std::make_shared<FScene>();
		}	
		//scene->set_busy();
		LOG_IF(!ImportScene(fbx_file), FATAL) << "Failed to import the scene from file: " << fbx_file;

		auto root_node = fbx_scene()->GetRootNode();
		LOG_IF(!root_node, FATAL) << "Failed to retrieve a root node";

		auto root_node_ch_count = root_node->GetChildCount();
		for (auto i = 0; i < root_node_ch_count; i++)
		{
			//as we import from root node, we haven't had a parent yet
			LoadComponent(scene, nullptr, root_node->GetChild(i));
		}
		//scene->set_free();
		return scene;
	}


	void FResourceLoader::LoadComponent(FShared<FScene>& scene, FShared<FEntity> parent, FbxNode * node)
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
				auto mesh = LoadMesh(node);
				scene->Add(mesh);
				current = std::static_pointer_cast<FEntity>(mesh);
				break;
			}
			//TODO: LOD group need to be reconsidered
			case FbxNodeAttribute::eLODGroup:
			{
				auto lod_group_mesh = LoadLodGroup(node);
				scene->Add(lod_group_mesh);
				current = std::static_pointer_cast<FEntity>(lod_group_mesh);
				return; // workaround for now
			}		
			case FbxNodeAttribute::eCamera:
			{
				auto camera = LoadCamera(node, scene);
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
		//TODO: better way to handle current, cause not all variants are listed in switch-case
		//LOG_IF(!current, FATAL) << "Failed to cast to FEntity";
		if (parent && current)
		{
			current->set_parent(parent);
			parent->AddChild(current);
		}
		auto node_ch_count = node->GetChildCount();
		for (auto i = 0; i < node_ch_count; i++)
		{
			LoadComponent(scene, current, node->GetChild(i));
		}
	}

	FShared<FMesh> FResourceLoader::LoadMesh(FbxNode *node)
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadMesh";
		auto mesh = LoadEntityBase<FMesh>(node);
		mesh->AddLod(LoadLod(node, FLT_MAX));
		return mesh;
	}

	uint64_t FResourceLoader::LoadUniqueId(FbxNode* node)
	{
		return static_cast<uint64_t>(node->GetUniqueID());
	}

	FString FResourceLoader::LoadName(FbxNode* node)
	{
		return FString(node->GetName());
	}

	/*
		Lod group of fbx can contain any object
		For us it's not relevant to handle any object as we need to load only meshes. If not mesh is met, a warning will be given. 
		Moreover, Maya allows to attach children to meshes of the lod group(in our case we call
		them "lods of the lod group")s. This method also doesn't take it into account and give a warning 
		if any mesh contain children.
	*/
	FShared<FMesh> FResourceLoader::LoadLodGroup(FbxNode * node)
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadLodGroup";
		
		auto fbx_lod_group = static_cast<FbxLodGroupLoader*>(node->GetNodeAttribute());
		LOG_IF(!fbx_lod_group, FATAL) << "Failed to cast to FbxLodGroupLoader";

		FVector<FMeshLod> lods;
		auto node_ch_count = node->GetChildCount();
		lods.reserve(node_ch_count);
		for (auto i = 0; i < node_ch_count; i++)
		{
			auto nodeChild = node->GetChild(i);
			LOG_IF(nodeChild->GetNodeAttribute()->GetAttributeType() != FbxNodeAttribute::eMesh, WARNING) << "Invalid element of LOD group. Must be mesh only";
			LOG_IF(nodeChild->GetChildCount() != 0, WARNING) << "Lods of lod group must not contain children";
			auto threshold = fbx_lod_group->RetrieveThreshold(i);
			lods.push_back(LoadLod(nodeChild, threshold));
		}
		auto mesh = LoadEntityBase<FMesh>(node);
		mesh->AddLods(lods);
		return mesh;
	}

	FMeshLod FResourceLoader::LoadLod(FbxNode * node, float threshold)
	{
		LOG_IF(!node, FATAL) << "nullptr node passed to LoadLod";
		auto fbx_mesh = static_cast<FbxMeshLoader*>(node->GetNodeAttribute());
		return FMeshLod(threshold, std::make_shared<FGeometry>(
			fbx_mesh->LoadIndices(),
			fbx_mesh->LoadVertices(),
			fbx_mesh->LoadUvs()));
	}

	FShared<FCamera> FResourceLoader::LoadCamera(FbxNode * node, FShared<FScene>& scene)
	{
		LOG_IF(!node, FATAL) << "Invalid node passed to LoadCamera";

		auto fbx_camera = static_cast<FbxCameraLoader*>(node->GetNodeAttribute());

		auto camera = LoadEntityBase<FCamera>(node);

		//if camera has aim, attach aimed entity to the camera`s target field
		//otherwise set target to specified position
		auto camera_target = node->GetTarget();
		if (camera_target)
		{
			camera->LookAt(scene->FindEntityById(camera_target->GetParent()->GetUniqueID()));
		} 
		else
		{
			camera->LookAt(fbx_camera->GetTarget());
		}	
		camera->set_aperture(fbx_camera->GetApperture());
		camera->set_aspect_ratio(static_cast<float>(fbx_camera->FilmAspectRatio.Get()));
		camera->set_focal_length(static_cast<float>(fbx_camera->FocalLength.Get()));
		camera->set_aspect_ratio(0.0f);		//TODO: get aspect ratio
		camera->set_znear(static_cast<float>(fbx_camera->NearPlane.Get()));
		camera->set_zfar(static_cast<float>(fbx_camera->FarPlane.Get()));
		camera->set_fovy(FAngle::Degrees(static_cast<float>(fbx_camera->FieldOfViewY.Get())));

		return camera;
	}

	FPoint3f FResourceLoader::LoadTransition(FbxNode * node)
	{
		return ToPoint3f(node->LclTranslation.Get());
	}

	FPoint3f FResourceLoader::LoadRotation(FbxNode* node)
	{
		return ToPoint3f(node->LclRotation.Get());
	}

	FPoint3f FResourceLoader::LoadScale(FbxNode* node)
	{
		return ToPoint3f(node->LclScaling.Get());
	}
}
