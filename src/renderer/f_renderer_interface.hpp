#ifndef _3FENGINE_SRC_RENDERER_F_RENDERER_INTERFACE_HPP
#define _3FENGINE_SRC_RENDERER_F_RENDERER_INTERFACE_HPP
#include <gui/f_window.hpp>

#include <scene/f_scene.hpp>

namespace fengine
{
	class FRendererInterface
	{
	public:
		FRendererInterface() = default;

		virtual ~FRendererInterface() = default;

		virtual void RenderFrame(float delta) = 0;

		virtual const FWindow& GetActiveWindow() = 0;

		virtual void BufferizeScene(FShared<FScene> scene) = 0;

	};
}

#endif // _3FENGINE_SRC_RENDERER_F_RENDERER_INTERFACE_HPP