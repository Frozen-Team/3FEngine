#ifndef _3FENGINE_SRC_ENGINE_HPP_
#define _3FENGINE_SRC_ENGINE_HPP_

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>
#include <fcomponents/f_logger.hpp>
#include <fcomponents/f_events_manager.hpp>
#include <settings/f_settings.hpp>

namespace fengine
{
	class Engine : public futils::FSingleton<Engine>
	{
		F_DISABLE_COPY(Engine)
	public:
		Engine();
		~Engine();

	private:
		FShared<FLogger> logger_;
		FShared<FSettings> settings_;
		FShared<FEventsManager> events_manager_;
	};
}

#endif // _3FENGINE_SRC_ENGINE_HPP_