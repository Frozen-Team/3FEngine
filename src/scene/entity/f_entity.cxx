#include "scene/entity/f_entity.hpp"

namespace fengine {
	// TODO: Proper initialization!
	FEntity::FEntity() : id_(0), type_(FEntityType::kNull) {}

	FEntity::FEntity(uint64_t id, const FString& name, const FEntityType& type, const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale) :
		name_(name), type_(type), parent_(nullptr)
	{
		this->set_id(id);
		this->SetTransition(transition);
		this->SetRotation(rotation);
		this->SetScale(scale);
	}

	void FEntity::AddChild(FShared<FEntity> child)
	{
		LOG_IF(child == nullptr, FATAL) << "Attempt to set an invalid child";
		LOG_IF(!child->HasParent() || child->parent()->id() != id_, FATAL) << "Invalid parent of a child. Parent has to be set before passing to AddChild";
		this->children_.push_back(child);
	}

	//TODO: need tests
	FShared<FEntity> FEntity::SearchInHierarchy(uint64_t id) const
	{
		auto result = this->GetChild(id);
		if (result) { return result; }
		for (auto it = this->cbegin(); it != this->cend() || !result; ++it)
		{
			result = this->SearchInHierarchy(id);
		}
		return result;
	}

	FShared<FEntity> FEntity::GetChild(uint64_t id) const
	{
		return FindEntityById(this->children_, id);
	}

	bool FEntity::HasParent() const
	{
		return this->parent_ != nullptr;
	}

	void FEntity::set_name(const FString& name)
	{
		this->name_ = name;
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

	void FEntity::set_type(FEntityType type)
	{
		this->type_ = type;
	}

	void FEntity::SetTransition(const FPoint3f & transition)
	{
		transform_.SetPointRow(FTransformationMatrix::Attribute::kTransition, transition);
	}
	void FEntity::SetRotation(const FPoint3f & rotation)
	{
		transform_.SetPointRow(FTransformationMatrix::Attribute::kRotation, rotation);
	}
	void FEntity::SetScale(const FPoint3f & scale)
	{
		transform_.SetPointRow(FTransformationMatrix::Attribute::kScale, scale);
	}
	FPoint3f FEntity::GetTransition() const
	{
		return transform_.GetPoint3fRow(FTransformationMatrix::Attribute::kTransition);
	}
	FPoint3f FEntity::GetRotation() const
	{
		return transform_.GetPoint3fRow(FTransformationMatrix::Attribute::kRotation);
	}
	FPoint3f FEntity::GetScale() const
	{
		return transform_.GetPoint3fRow(FTransformationMatrix::Attribute::kScale);
	}

}
