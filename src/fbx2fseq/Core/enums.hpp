#ifndef FBX2FSEQ_SRC_CORE_ENUMS_HPP_
#define FBX2FSEQ_SRC_CORE_ENUMS_HPP_

enum TypeId{
	kScenesId = 446508053,
	kSceneId = 541744780,
	kMeshId = 830987706,
	kMeshTransformId = 516947731,
	kMeshLodId = 723215762,
	kVertices3fId = 331750911,
	kVertexIndicesId = 958406796,
	kTextureCoordsId = 213954678,
	kTextureIndicesId = 364779684,
};

enum WriteReadCmds {
	kScene,
	kMesh,

};
#endif // FBX2FSEQ_SRC_CORE_ENUMS_HPP_