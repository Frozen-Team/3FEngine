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
		this->SetPointRow(0, transition);
	}
	void FTransformationMatrix::SetRotation(const FPoint3f & rotation)
	{
		this->SetPointRow(1, rotation);
	}
	FPoint3f FTransformationMatrix::GetTransition() const
	{
		return this->GetPointRow(0);
	}
	FPoint3f FTransformationMatrix::GetScale() const
	{
		return this->GetPointRow(2);
	}
	FPoint3f FTransformationMatrix::GetRotation() const
	{
		return this->GetPointRow(1);
	}
	void FTransformationMatrix::SetScale(const FPoint3f & scale)
	{
		this->SetPointRow(2, scale);
	}
	void FTransformationMatrix::Reset()
	{
		this->value_ = Eigen::MatrixXf::Zero(4, 4);
		this->value_(3, 3) = 1.0f;
	}
	
	void FTransformationMatrix::SetPointRow(int row, const FPoint3f& row_to_set)
	{
		LOG_IF(row < 0, FATAL) << "Index of row must be greater than 0";
		for (int i = 0; i < 3; i++) 
		{
			this->value_(row, i) = row_to_set(i);
		}
	}

	FPoint3f FTransformationMatrix::GetPointRow(int row) const
	{
		LOG_IF(row < 0, FATAL) << "Index of row must be greater than 0";
		FPoint3f result;
		for (int i = 0; i < 3; i++)
		{
			result(i) = this->value_(row, i);
		}
		return result;
	}

}

