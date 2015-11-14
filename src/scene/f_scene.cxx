#include "f_scene.hpp"

namespace fengine {
	FShared<FEntity> FScene::FindEntityById(uint64_t id) const
	{
		auto resultEntity = FEntity::FindEntityById(this->meshes_, id);
		if (resultEntity) { return resultEntity; }
		resultEntity = FEntity::FindEntityById(this->cameras_, id);
		return resultEntity ? resultEntity : nullptr;
	}
}
