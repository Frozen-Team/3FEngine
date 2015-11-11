#include "scene/entity/f_entity.hpp"

namespace fengine {
	FEntity::FEntity() : parent_(nullptr) {}

	void FEntity::AddChild(FShared<FEntity> child)
	{
		this->children_.push_back(child);
	}

	void FEntity::set_parent(FShared<FEntity> parent)
	{
		this->parent_ = parent;
	}
}
