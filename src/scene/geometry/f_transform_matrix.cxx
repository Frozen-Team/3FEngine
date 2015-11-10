#include "f_transform_matrix.hpp"
#include "fcomponents/f_logger.hpp"
namespace fengine
{
	FTransformationMatrix::FTransformationMatrix()
	{
		this->Reset();
	}

	FTransformationMatrix::FTransformationMatrix(const FPoint3f & transition, const FPoint3f & rotation, const FPoint3f & scale)
	{
		this->Reset();
		this->SetTransition(transition);
		this->SetRotation(rotation);
		this->SetScale(scale);
	}

	void FTransformationMatrix::SetTransition(const FPoint3f & transition)
	{
		this->SetPointRow(Attribute::kTransition, transition);
	}
	void FTransformationMatrix::SetRotation(const FPoint3f & rotation)
	{
		this->SetPointRow(Attribute::kRotation, rotation);
	}
	void FTransformationMatrix::SetScale(const FPoint3f & scale)
	{
		this->SetPointRow(Attribute::kScale, scale);
	}
	FPoint3f FTransformationMatrix::GetTransition() const
	{
		return this->GetPointRow(Attribute::kTransition);
	}	
	FPoint3f FTransformationMatrix::GetRotation() const
	{
		return this->GetPointRow(Attribute::kRotation);
	}
	FPoint3f FTransformationMatrix::GetScale() const
	{
		return this->GetPointRow(Attribute::kScale);
	}
	
	void FTransformationMatrix::Reset()
	{
		this->value_ = Eigen::MatrixXf::Zero(4, 4);
		this->value_(3, 3) = 1.0f;
	}
	
	void FTransformationMatrix::SetPointRow(int row, const FPoint3f& row_to_set)
	{
		LOG_IF(row < 0, FATAL) << "Index of row must be greater than 0";
		this->value_.block<1, 3>(row, 0) = row_to_set;
	}

	FPoint3f FTransformationMatrix::GetPointRow(int row) const
	{
		LOG_IF(row < 0, FATAL) << "Index of row must be greater than 0";
		return this->value_.block<1, 3>(row, 0);
	}

}

