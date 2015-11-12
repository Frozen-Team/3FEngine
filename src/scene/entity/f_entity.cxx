#include "scene/entity/f_entity.hpp"
#include "fcomponents/f_logger.hpp"
namespace fengine {
	FEntity::FEntity() : id_(0), type_(FEntityType::kNull) {}

	FEntity::FEntity(uint64_t id, FEntityType type, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale) : 
		FTransformationMatrix(transition, rotation, scale), type_(type), parent_(nullptr)
	{
		this->set_id(id);
	}

	void FEntity::AddChild(FShared<FEntity> child)
	{
		LOG_IF(child == nullptr, FATAL) << "Attempt to set an invalid child";
		this->children_.push_back(child);
	}

	void FEntity::set_parent(FShared<FEntity> parent)
	{
		LOG_IF(parent == nullptr, FATAL) << "Attempt to set an invalid parent";
		this->parent_ = parent;
	}

	void FEntity::set_id(uint64_t id)
	{
		LOG_IF(id < 0, FATAL) << "Unique id must be >= 0";
		this->id_ = id;
	}
}
