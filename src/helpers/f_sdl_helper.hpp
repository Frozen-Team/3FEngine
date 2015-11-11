#ifndef _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_
#define _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>
#include <renderer/f_renderer_enums.hpp>

namespace fengine
{
	class FSdlHelper : public futils::FSingleton<FSdlHelper>
	{
		F_DISABLE_COPY(FSdlHelper)
	public:
		FSdlHelper() = default;

		virtual ~FSdlHelper() = default;

		static bool CheckError() noexcept;

		static const FString& GetLastError() noexcept;

	private:
		friend class Engine;

		static int Initialize();

		static FString last_error_;
	};
}

#endif // _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_