#ifndef _3FENGINE_SRC_UTILS_F_SINGLETON_HPP_
#define _3FENGINE_SRC_UTILS_F_SINGLETON_HPP_

#include <assert.h>
#include "utils/f_typedefs.hpp"

namespace fengine
{
	namespace futils
	{
		template<typename T>
		class FSingleton
		{
			F_DISABLE_COPY(FSingleton)
		public:

			virtual ~FSingleton() {}

			static FShared<T> GetInstance()
			{
				if (!instance) {
					instance = std::make_shared<T>();
				}
				assert(instance && "Error creating instance.");
				return instance;
			}

			static void Release() {
				assert(instance && "Trying to delete non existing instance.");
				instance.reset();
			}

		protected:
			FSingleton() {};

		private:
			static FShared<T> instance;
		};

		template<typename T>
		FShared<T> FSingleton<T>::instance = nullptr;
	};
}

#endif // _3FENGINE_SRC_UTILS_F_SINGLETON_HPP_
