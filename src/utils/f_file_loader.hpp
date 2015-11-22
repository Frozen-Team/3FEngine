#ifndef _3FENGINE_SRC_UTILS_F_FILE_LOADER_HPP
#define _3FENGINE_SRC_UTILS_F_FILE_LOADER_HPP

#include <utils/f_typedefs.hpp>

namespace fengine
{
	namespace futils
	{
		class FFileLoader
		{
		public:
			FFileLoader() = default;

			explicit FFileLoader(const FString& file_path);

			void LoadFile(const FString& file_path);

			const FString& ToString();

		private:
			FString data;
		};
	}
}

#endif // _3FENGINE_SRC_UTILS_F_FILE_LOADER_HPP