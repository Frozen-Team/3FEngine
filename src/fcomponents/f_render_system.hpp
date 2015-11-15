#ifndef _3FENGINE_SRC_RENDERER_F_RENDER_SYSTEM_HPP
#define _3FENGINE_SRC_RENDERER_F_RENDER_SYSTEM_HPP

#include <utils/f_typedefs.hpp>
#include <renderer/f_renderer_interface.hpp>
#include <scene/f_scene.hpp>

namespace fengine
{
	class FRenderSystem final : futils::FSingleton<FRenderSystem>
	{
		friend class Engine;
		F_DISABLE_COPY(FRenderSystem)
	public:
		// TODO: Scene caching mechanism
		FRenderSystem();

		virtual ~FRenderSystem();

		template<typename Renderer>
		static void Initialize()
		{
			renderer_ = std::make_unique<Renderer>();
		}

		static void SetActiveScene(FShared<FScene> scene);

		static void SetActiveCamera(FShared<FCamera> camera);

		static void RenderFrame(float delta);

	private:
		static FUnique<FRendererInterface> renderer_;
		static FShared<FScene> active_scene_;
		static FShared<FCamera> active_camera_;
	};
}

#endif // _3FENGINE_SRC_RENDERER_F_RENDER_SYSTEM_HPP