#ifndef _3FENGINE_SRC_COMPONENTS_F_LOGGER_HPP_
#define _3FENGINE_SRC_COMPONENTS_F_LOGGER_HPP_

#define ELPP_DEBUG_ERRORS
#define ELPP_THREAD_SAFE
#define ELPP_FORCE_USE_STD_THREAD
#define ELPP_NO_DEFAULT_LOG_FILE
#define ELPP_DEFAULT_LOG_FILE "custom.log"
#include "easylogging++.h"

#include <utils/f_typedefs.hpp>
#include "../utils/f_singleton.hpp"

namespace fengine {
	class FLogger : public futils::FSingleton<FLogger>
	{
		F_DISABLE_COPY(FLogger)
	public:
		FLogger();
		~FLogger();

		static int SetDefaultConfiguration();

		static int LoadConfiguration(const FString& file_name);

		static int SetConfiguration(const FString& str_cfg);

	private:
		const static FString kDefaultConfiguration;
		//const static std::function<char*(void)> kNewLineSpecifier;
	};
}

#endif // _3FENGINE_SRC_COMPONENTS_F_LOGGER_HPP_