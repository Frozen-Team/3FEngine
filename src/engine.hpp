#ifndef _3FENGINE_SRC_ENGINE_HPP_
#define _3FENGINE_SRC_ENGINE_HPP_

#include "utils\f_typedefs.hpp"
#include "utils\f_singleton.hpp"
#include "components\f_logger.hpp"
// _3FENGINE_SRC_ENGINE_HPP_
namespace fengine {
	class Engine : public futils::FSingleton<Engine> {
		F_DISABLE_COPY(Engine)// _3FENGINE_SRC_ENGINE_HPP_
	public:
		Engine(); //
		~Engine();

	private:
		FShared<FLogger> logger_;// _3FENGINE_SRC_ENGINE_HPP_
	};
}

#endif // _3FENGINE_SRC_ENGINE_HPP_