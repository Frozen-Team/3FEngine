#ifndef _3FENGINE_SRC_F_COMPONENTS_F_SCENES_MANAGER_HPP_
#define _3FENGINE_SRC_F_COMPONENTS_F_SCENES_MANAGER_HPP_

#include <utils/f_singleton.hpp>

namespace fengine
{
	class FScenesManager final : private futils::FSingleton<FScenesManager>
	{
		friend class Engine;
		F_DISABLE_COPY(FScenesManager)
	public:
		FScenesManager() = default;
		virtual ~FScenesManager() = default;
	};
}

#endif // _3FENGINE_SRC_F_COMPONENTS_F_SCENES_MANAGER_HPP_