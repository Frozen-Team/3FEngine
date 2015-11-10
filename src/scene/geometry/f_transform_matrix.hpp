#ifndef _3FENGINE_SRC_SCENE_GEOMETRY_F_TRANSFORMATION_MATRIX_HPP
#define _3FENGINE_SRC_SCENE_GEOMETRY_F_TRANSFORMATION_MATRIX_HPP

#include <utils/f_typedefs.hpp>

namespace fengine
{
	// transition.x		transition.y	 transition.z	0
	// rotation.x		rotation.y		 rotation.z		0
	// scale.x			scale.y			 scale.z		0
	//      0				 0				  0			1
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
		FTransformationMatrix(const FPoint3f& transition, const FPoint3f& rotation, const FPoint3f& scale);
		virtual ~FTransformationMatrix() = default;

		void SetTransition(const FPoint3f& transition);
		void SetScale(const FPoint3f& scale);
		void SetRotation(const FPoint3f& rotation);
		
		FPoint3f GetTransition() const;
		FPoint3f GetScale() const;
		FPoint3f GetRotation() const;
		void Reset();
		FMatrix4f& value() { return this->value_; }
	private:
		
		void SetPointRow(int row, const FPoint3f& row_to_set);
		FPoint3f GetPointRow(int row) const;
	private:
		FMatrix4f value_;
	};
}
#endif // _3FENGINE_SRC_SCENE_GEOMETRY_F_TRANSFORMATION_MATRIX_HPP