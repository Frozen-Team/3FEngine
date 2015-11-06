#include "fbx_mesh_loader.hpp"
#include <algorithm>
#include <iterator>

namespace fengine 
{
	FVertices3f FbxMeshLoader::LoadVertices()
	{
		auto fbx_vertices = this->GetControlPoints();
		auto fbx_vertices_count = this->GetControlPointsCount();
		FVertices3f::Vector vertices;
		vertices.reserve(fbx_vertices_count * 3);

		for (int i = 0; i < fbx_vertices_count; i++) {
			vertices.push_back(static_cast<float>(fbx_vertices[i][0]));
			vertices.push_back(static_cast<float>(fbx_vertices[i][1]));
			vertices.push_back(static_cast<float>(fbx_vertices[i][2]));
		}

		return FVertices3f(vertices);
	}
	FIndices3 FbxMeshLoader::LoadIndices()
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
		return FUvsf();
	}
}