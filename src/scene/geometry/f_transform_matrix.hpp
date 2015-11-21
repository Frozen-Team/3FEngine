#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_F_TRANSFORMATION_MATRIX_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_F_TRANSFORMATION_MATRIX_HPP

#include <utils/f_typedefs.hpp>

namespace fengine
{
	// transition.x		transition.y	transition.z	0
	// rotation.x		rotation.y		rotation.z		0
	// scale.x			scale.y			scale.z			0
	//	0				0				0				1
	//
	//FPoint3f is column vector, be careful
	class FTransformationMatrix
	{
	public:
		enum Attribute
		{
			kTransition,
			kRotation,
			kScale
		};

		FTransformationMatrix();
		virtual ~FTransformationMatrix() = default;
		
		//Set each element to zero and the element in right bottom conner to 1.0f
		void Reset();
		FMatrix4f data() const noexcept { return this->data_; }

		void SetPointRow(int row, const FPoint3f& row_to_set);
		FPoint3f GetPoint3fRow(int row) const;

	private:
		FMatrix4f data_;
	};
}
#endif // _3FENGINE_SRC_SCENE_GEOMETRY_F_TRANSFORMATION_MATRIX_HPP