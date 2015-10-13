#ifndef _3FENGINE_SRC_UTILS_SINGLETON_HPP_
#define _3FENGINE_SRC_UTILS_SINGLETON_HPP_

#include <memory>
#include <assert.h>

namespace FEngine {
	namespace Utils {
		template<typename T>
		class Singleton {
		public:
			Singleton() {
				assert(!instance && "Trying to create another instance of singleton object.");
				instance = std::shared_ptr<T>(static_cast<T*>(this));
			}

			~Singleton() {
				assert(instance);
			}

			static T& GetInstance() {
				assert(instance);
				return *instance;
			}

		private:
			Singleton(const Singleton<T>&) = delete;
			Singleton& operator=(const Singleton<T>) = delete;

		protected:
			static std::shared_ptr<T> instance;
		};
	}
}

#endif // _3FENGINE_SRC_UTILS_SINGLETON_HPP_

