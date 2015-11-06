#include "fbx_mesh_loader.hpp"
#include <algorithm>
#include <iterator>

namespace fengine
{
	FVertices3f FbxMeshLoader::LoadVertices() const
	{
		auto fbx_vertices = this->GetControlPoints();
		auto fbx_vertices_count = this->GetControlPointsCount();
		FVertices3f::Vector vertices;
		vertices.reserve(fbx_vertices_count * 3);

		for (auto i = 0; i < fbx_vertices_count; i++) {
			vertices.push_back(static_cast<float>(fbx_vertices[i][0]));
			vertices.push_back(static_cast<float>(fbx_vertices[i][1]));
			vertices.push_back(static_cast<float>(fbx_vertices[i][2]));
		}
		return FVertices3f(vertices);
	}
	FIndices3 FbxMeshLoader::LoadIndices() const
	{
		auto fbx_indices = this->GetPolygonVertices();
		auto fbx_indices_count = this->GetPolygonVertexCount();
		FIndices3::Vector indices;
		indices.reserve(fbx_indices_count);
		std::copy(fbx_indices, fbx_indices + fbx_indices_count, std::back_inserter(indices));

		return FIndices3(indices);
	}

	FUvsf FbxMeshLoader::LoadUvs()
	{
		FUvsf uvs;
		FbxStringList uv_set_name_list;
		this->GetUVSetNames(uv_set_name_list);

		std::string uv_set_name;
		FbxGeometryElementUV* uv_element = nullptr;
		//iterating over all uv sets
		auto uv_set_names_count = uv_set_name_list.GetCount();
		for (auto lUVSetIndex = 0; lUVSetIndex < uv_set_names_count; lUVSetIndex++)
		{
			uv_set_name = uv_set_name_list.GetStringAt(lUVSetIndex);
			uv_element = this->GetElementUV(uv_set_name.c_str());

			if (!uv_element)
				continue;

			auto strategy = uv_element->GetMappingMode();

			// only support mapping mode eByPolygonVertex and eByControlPoint
			if (strategy != FbxGeometryElement::eByPolygonVertex &&
				strategy != FbxGeometryElement::eByControlPoint)
				LOG(FATAL) << "Unsupported mapping mode";

			//index array, where holds the index referenced to the uv data
			auto use_index = uv_element->GetReferenceMode() != FbxGeometryElement::eDirect;
			auto l_index_count = (use_index) ? uv_element->GetIndexArray().GetCount() : 0;

			//variables used in the following loops
			const auto poly_count = this->GetPolygonCount();
			FbxVector2 uv_value;

			auto poly_index_counter = 0;
			auto uv_index = 0;
			int poly_vert_index;

			for (auto lPolyIndex = 0; lPolyIndex < poly_count; ++lPolyIndex)
			{
				const auto lPolySize = this->GetPolygonSize(lPolyIndex);
				for (auto lVertIndex = 0; lVertIndex < lPolySize; ++lVertIndex)
				{
					switch (strategy)
					{
					case FbxGeometryElement::eByControlPoint:
						poly_vert_index = this->GetPolygonVertex(lPolyIndex, lVertIndex);
						uv_index = use_index ? uv_element->GetIndexArray().GetAt(poly_vert_index) : poly_vert_index;
						break;
					case FbxGeometryElement::eByPolygonVertex:
						if (!(poly_index_counter < l_index_count)) { continue; }
						uv_index = use_index ? uv_element->GetIndexArray().GetAt(poly_index_counter) : poly_index_counter;
						poly_index_counter++;
						break;
					}
					uv_value = uv_element->GetDirectArray().GetAt(uv_index);
					uvs.Add({ static_cast<float>(uv_value.mData[0]) , static_cast<float>(uv_value.mData[1])});	
				}
			}
		}
		return uvs;
	}
}
