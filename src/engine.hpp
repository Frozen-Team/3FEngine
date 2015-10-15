#ifndef _3FENGINE_SRC_ENGINE_HPP_
#define _3FENGINE_SRC_ENGINE_HPP_

#include "utils\f_typedefs.hpp"
#include "utils\f_singleton.hpp"
#include "components\f_logger.hpp"

namespace fengine {
	class Engine : public futils::FSingleton<Engine> {
		F_DISABLE_COPY(Engine)
	public:
		Engine();
		~Engine();

	private:
		FShared<FLogger> logger_;
	};
}

#endif // _3FENGINE_SRC_ENGINE_HPP_