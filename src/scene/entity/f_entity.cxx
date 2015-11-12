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

	FShared<FEntity> FEntity::SerachInHierarchy(uint64_t id) const
	{
		auto result = this->GetChild(id);
		if (result) { return result; }
		for (auto it = this->cbegin(); it != this->cend(); ++it)
		{
			this->SerachInHierarchy(id);
		}
		return nullptr;
	}

	FShared<FEntity> FEntity::GetChild(uint64_t id) const
	{
		auto result = std::find_if(this->cbegin(), this->cend(), [id](FShared<FEntity> el) { return el->id() == id; });
		return (result == this->cend()) ? nullptr : *result;
	}

	bool FEntity::HasParent() const
	{
		return this->parent_ != nullptr;
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
