#ifndef _3FENGINE_SRC_ENGINE_HPP_
#define _3FENGINE_SRC_ENGINE_HPP_

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>
#include <fcomponents/f_logger.hpp>
#include <fcomponents/f_events_manager.hpp>
#include <settings/f_settings.hpp>
#include <helpers/f_sdl_helper.hpp>
#include <f_main_loop_interface.hpp>

namespace fengine
{
	class Engine : public futils::FSingleton<Engine>
	{
		F_DISABLE_COPY(Engine)
	public:
		Engine();
		~Engine();

		void Initialize(FUnique<FMainLoopInterface> main_loop);

		int Exec() const;

	private:
		FShared<FLogger> logger_;
		FShared<FSettings> settings_;
		FShared<FSdlHelper> sdl_helper_;
		FShared<FEventsManager> events_manager_;
		FUnique<FMainLoopInterface> main_loop_;
	};
}

#endif // _3FENGINE_SRC_ENGINE_HPP_