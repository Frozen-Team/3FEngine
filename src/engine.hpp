#ifndef _3FENGINE_SRC_ENGINE_HPP_
#define _3FENGINE_SRC_ENGINE_HPP_

#include "utils\typedefs.hpp"
#include "utils\f_singleton.hpp"
#include "components\logger.hpp"

namespace FEngine {
	class Engine : public Utils::FSingleton<Engine> {
		F_DISABLE_COPY(Engine)
	public:
		Engine();
		~Engine();

	private:
		FShared<FLogger> logger_;
	};
}

#endif // _3FENGINE_SRC_ENGINE_HPP_