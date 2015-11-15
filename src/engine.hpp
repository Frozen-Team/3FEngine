#ifndef _3FENGINE_SRC_ENGINE_HPP_
#define _3FENGINE_SRC_ENGINE_HPP_

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>

#include <fcomponents/f_logger.hpp>
#include <fcomponents/f_render_system.hpp>
#include <settings/f_settings.hpp>

#include <f_main_loop_interface.hpp>

namespace fengine
{
	class Engine final : public futils::FSingleton<Engine>
	{
		F_DISABLE_COPY(Engine)
	public:
		Engine();

		virtual ~Engine();

		template<typename MainLoopClass, typename Renderer>
		void Initialize()
		{
			main_loop_ = std::move(std::make_unique<MainLoopClass>());
			LOG_IF(!main_loop_, FATAL) << "Cannot allocate memory for the main loop.";
			FRenderSystem::Initialize<Renderer>();
		}

		int Exec() const;

	private:
		FShared<FSettings> settings_;
		FUnique<FMainLoopInterface> main_loop_;
	};
}

#endif // _3FENGINE_SRC_ENGINE_HPP_