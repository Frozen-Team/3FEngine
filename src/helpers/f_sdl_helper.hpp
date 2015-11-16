#ifndef _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_
#define _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_

#include <utils/f_typedefs.hpp>
#include <utils/f_singleton.hpp>

namespace fengine
{
	class FSdlHelper : public futils::FSingleton<FSdlHelper>
	{
		F_DISABLE_COPY(FSdlHelper)
	public:
		FSdlHelper();

		virtual ~FSdlHelper();

		static bool CheckError() noexcept;

		static const FString& GetLastError() noexcept;

	private:
		friend class Engine;

		static int Initialize();

		static FString last_error_;
	};
}

#endif // _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_