#include "fbx_mesh_loader.hpp"
namespace fengine 
{
	FVertices3f FbxMeshLoader::LoadVertices()
	{
		auto fbx_vertices = this->GetControlPoints();
		auto fbx_vertices_count = this->GetControlPointsCount();
		FVectorf verticesf;
		verticesf.reserve(fbx_vertices_count * 3);

		for (int i = 0; i < fbx_vertices_count; i++) {
			verticesf.push_back(static_cast<float>(fbx_vertices[i][0]));
			verticesf.push_back(static_cast<float>(fbx_vertices[i][1]));
			verticesf.push_back(static_cast<float>(fbx_vertices[i][2]));
		}
		return FVertices3f(verticesf);
	}
	FIndices3 FbxMeshLoader::LoadIndices()
	{
		auto fbx_indices = this->GetPolygonVertices();
		auto fbx_indices_count = this->GetPolygonVertexCount();
		auto indices = FVectori();
		indices.reserve(fbx_indices_count);
		std::copy(fbx_indices, fbx_indices + fbx_indices_count, indices.begin());

		return FIndices3(indices);
	}
	FUvsf FbxMeshLoader::LoadUvs()
	{
		return FUvsf();
	}
}