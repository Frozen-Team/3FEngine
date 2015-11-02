#include "f_resource_loader.hpp"

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
				break;
			case FbxNodeAttribute::eCamera:
				break;
			}
		}
	}

	FShared<FMesh> FResourceLoader::LoadMesh(FbxNode *node)
	{
		FShared<FMesh> f_mesh = std::make_shared<FMesh>();
		auto fbx_mesh = (FbxMesh*)node;

		// retrieve vertices coord XYZ
		auto fbx_vertices = fbx_mesh->GetControlPoints();
		auto fbx_vertices_count = fbx_mesh->GetControlPointsCount();
		FVector<float> float_vertices;
		float_vertices.reserve(fbx_vertices_count * 3);
		for (int i = 0; i < fbx_vertices_count; i++) {
			float_vertices.push_back(fbx_vertices[i][0]);
			float_vertices.push_back(fbx_vertices[i][1]);
			float_vertices.push_back(fbx_vertices[i][2]);
		}
		auto f_vertices = FVertices3f(float_vertices);

		//retrieve indices
		auto fbx_indices = fbx_mesh->GetPolygonVertices();
		auto fbx_indices_count = fbx_mesh->GetPolygonVertexCount();
		auto indices_vector = FVector<int>();
		indices_vector.reserve(fbx_indices_count);
		std::copy(fbx_indices, fbx_indices + fbx_indices_count, indices_vector.begin());

		auto f_indices = FIndices3(indices_vector);

		auto f_uvs = this->LoadUvs(fbx_mesh);
		//retrieve 
		auto geometry = std::make_shared<FGeometry>(f_indices, f_vertices, f_uvs);

		f_mesh->AddLod(0, geometry);
		return f_mesh;
	}

	FUvsf & FResourceLoader::LoadUvs(FbxMesh * mesh)
	{
		FUvsf uvs;
	//	//get all UV set names
	//	FbxStringList lUVSetNameList;
	//	mesh->GetUVSetNames(lUVSetNameList);

	//	//iterating over all uv sets
	//	for (int lUVSetIndex = 0; lUVSetIndex < lUVSetNameList.GetCount(); lUVSetIndex++)
	//	{
	//		//get lUVSetIndex-th uv set
	//		const char* lUVSetName = lUVSetNameList.GetStringAt(lUVSetIndex);
	//		const FbxGeometryElementUV* lUVElement = mesh->GetElementUV(lUVSetName);

	//		if (!lUVElement)
	//			continue;

	//		// only support mapping mode eByPolygonVertex and eByControlPoint
	//		if (lUVElement->GetMappingMode() != FbxGeometryElement::eByPolygonVertex &&
	//			lUVElement->GetMappingMode() != FbxGeometryElement::eByControlPoint)
	//			return;

	//		//index array, where holds the index referenced to the uv data
	//		auto lUseIndex = lUVElement->GetReferenceMode() != FbxGeometryElement::eDirect;
	//		auto lIndexCount = (lUseIndex) ? lUVElement->GetIndexArray().GetCount() : 0;

	//		//iterating through the data by polygon
	//		const int lPolyCount = mesh->GetPolygonCount();
	//		FbxVector2 lUVValue;
	//		if (lUVElement->GetMappingMode() == FbxGeometryElement::eByControlPoint)
	//		{
	//			for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
	//			{
	//				// build the max index array that we need to pass into MakePoly
	//				const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
	//				for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
	//				{
	//					//get the index of the current vertex in control points array
	//					int lPolyVertIndex = mesh->GetPolygonVertex(lPolyIndex, lVertIndex);

	//					//the UV index depends on the reference mode
	//					int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyVertIndex) : lPolyVertIndex;

	//					lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

	//					//uvs.Add(lUVValue[0], lUVValue[1]);
	//				}
	//			}
	//		}
	//		else if (lUVElement->GetMappingMode() == FbxGeometryElement::eByPolygonVertex)
	//		{
	//			int lPolyIndexCounter = 0;
	//			for (int lPolyIndex = 0; lPolyIndex < lPolyCount; ++lPolyIndex)
	//			{
	//				// build the max index array that we need to pass into MakePoly
	//				const int lPolySize = mesh->GetPolygonSize(lPolyIndex);
	//				for (int lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
	//				{
	//					if (lPolyIndexCounter < lIndexCount)
	//					{
	//						//the UV index depends on the reference mode
	//						int lUVIndex = lUseIndex ? lUVElement->GetIndexArray().GetAt(lPolyIndexCounter) : lPolyIndexCounter;

	//						lUVValue = lUVElement->GetDirectArray().GetAt(lUVIndex);

	//						//uvs.Add(lUVValue[0], lUVValue[1]);

	//						lPolyIndexCounter++;
	//					}
	//				}
	//			}
	//		}
	//	}
		return uvs;
	}
}