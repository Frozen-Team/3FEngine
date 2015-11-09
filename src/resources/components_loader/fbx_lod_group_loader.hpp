#include "fbxsdk.h"

#include <utils/f_typedefs.hpp>

namespace fengine
{
	class FbxLodGroupLoader : public FbxLODGroup
	{
	public:
		F_DEFAULT_CTOR_V_DTOR(FbxLodGroupLoader)
		float RetrieveThreshold(int index) const;
	};
}