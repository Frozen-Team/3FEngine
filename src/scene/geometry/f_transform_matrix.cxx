#include "f_transform_matrix.hpp"
#include "fcomponents/f_logger.hpp"
namespace fengine
{
	FTransformationMatrix::FTransformationMatrix()
	{
		this->Reset();
	}
	
	void FTransformationMatrix::Reset()
	{
		this->data_ = Eigen::MatrixXf::Zero(4, 4);
		this->data_(3, 3) = 1.0f;
	}
	
	void FTransformationMatrix::SetPointRow(int row, const FPoint3f& row_to_set)
	{
		LOG_IF(row < 0, FATAL) << "Index of row must be greater than 0";
		this->data_.block<1, 3>(row, 0) = row_to_set;
	}

	FPoint3f FTransformationMatrix::GetPoint3fRow(int row) const
	{
		LOG_IF(row < 0, FATAL) << "Index of row must be greater than 0";
		return this->data_.block<1, 3>(row, 0);
	}

}

