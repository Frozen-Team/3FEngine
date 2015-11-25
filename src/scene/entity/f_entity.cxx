#include "scene/entity/f_entity.hpp"
#include <utils/f_entity_id_manager.hpp>

namespace fengine {

	FEntity::FEntity(const FEntityId& id, const FEntityType& type) : 
		FEntity(id, type, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f}, { 1.0f, 1.0f, 1.0f }) {}

	FEntity::FEntity(const FEntityId& id, const FEntityType& type, const FPos3f& pos, const FPoint3f& rotation, const FScale3f& scale) 
		:
		id_(id),
		type_(type),
		position_(pos), 
		rotation_(rotation), 
		scale_(scale),
		transform_old(Eigen::Matrix3f::Identity()),
		parent_(nullptr)
	{
		this->set_position(pos);
		this->set_rotation(rotation);
		this->set_scale(scale);
	}

	void FEntity::AddChild(FShared<FEntity> child)
	{
		LOG_IF(child == nullptr, FATAL) << "Attempt to set an invalid child";
		LOG_IF(!child->HasParent() || child->parent()->id() != id_.data(), FATAL) << "Invalid parent of a child. Parent has to be set before passing to AddChild";
		this->children_.push_back(child);
	}

	//TODO: need tests
	// TODO: FEntity Id storage class, FEntity id manager
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

	void FEntity::set_parent(FShared<FEntity> parent)
	{
		LOG_IF(parent == nullptr, FATAL) << "Attempt to set an invalid parent";
		this->parent_ = parent;
	}


	void FEntity::set_type(FEntityType type)
	{
		this->type_ = type;
	}


	void FEntity::set_position(const FPos3f& position)
	{
		this->position_ = position;
		UpdateTransform();
	}

	void FEntity::set_scale(const FScale3f& scale)
	{
		this->scale_ = scale;
		UpdateTransform();
	}

	void FEntity::set_rotation(const FPoint3f& rotation)
	{
		this->rotation_ = rotation;
		UpdateTransform();
	}

	void FEntity::move(const FPos3f& dp)
	{
		this->position_ += dp;
		this->transform_old.translate(dp);
		UpdateTransform();
	}

	void FEntity::rotate(const FQuaternionf& dr)
	{
		rotate(FPoint3f(dr.vec()));
	}

	void FEntity::rotate(const Eigen::Vector3f& dr)
	{
		this->rotation_ += dr;

		this->rotation_.x() = -std::remainderf(this->rotation_.x(), static_cast<float>(2 * M_PI));
		this->rotation_.y() = -std::remainderf(this->rotation_.y(), static_cast<float>(2 * M_PI));
		this->rotation_.z() = -std::remainderf(this->rotation_.z(), static_cast<float>(2 * M_PI));

		this->transform_old.rotate(Eigen::AngleAxisf(dr.z(), Eigen::Vector3f::UnitZ()));
		this->transform_old.rotate(Eigen::AngleAxisf(dr.y(), Eigen::Vector3f::UnitY()));
		this->transform_old.rotate(Eigen::AngleAxisf(dr.x(), Eigen::Vector3f::UnitX()));
	}

	void FEntity::scale(const FScale3f& ds)
	{
		/*FMatrix3f m3(FMatrix3f::Identity());
		FMatrix3f m3_scale(FMatrix3f::Zero());
		m3_scale.col(2) = ds;
		this->scale_ = m3 * m3_scale * this->scale_;
		this->transform_old.scale(this->scale_);*/
	}

	void FEntity::UpdateTransform()
	{
	}
}
