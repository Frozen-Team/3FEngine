#ifndef _3FENGINE_SRC_RENDERER_F_RENDERER_INTERFACE_HPP
#define _3FENGINE_SRC_RENDERER_F_RENDERER_INTERFACE_HPP

namespace fengine
{
	class FRendererInterface
	{
	public:
		FRendererInterface() = default;

		virtual ~FRendererInterface() = default;

		virtual void RenderFrame(float delta) = 0;

	};
}

#endif // _3FENGINE_SRC_RENDERER_F_RENDERER_INTERFACE_HPP