#ifndef _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_
#define _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_

#include <utils/f_typedefs.hpp>

namespace fengine
{
	class FSdlHelper
	{
	public:
		static bool CheckError() noexcept;

		static const FString& GetLastError() noexcept;

	private:
		static FString last_error_;
	};
}

#endif // _3FENGINE_SRC_HELPERS_F_SDL_HELPER_HPP_