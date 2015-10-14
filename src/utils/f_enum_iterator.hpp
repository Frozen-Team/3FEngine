#ifndef _3FENGINE_SRC_UTILS_F_ENUM_ITERATOR_HPP_
#define _3FENGINE_SRC_UTILS_F_ENUM_ITERATOR_HPP_

namespace FEngine {
	namespace FUtils {
		template<typename T>
		class FEnumIterator
		{
		public:
			class Iterator {
			public:
				Iterator(int value) : value_(value) {}

				T operator*() const
				{
					return (T)value_;
				}

				void operator++()
				{
					++value_;
				}

				bool operator!=(Iterator rhs)
				{
					return value_ != rhs.value_;
				}
			private:
				int value_;
			};
		};

		template<typename T>
		typename FEnumIterator<T>::Iterator begin(FEnumIterator<T>)
		{
			return typename FEnumIterator<T>::Iterator((int)T::First);
		}

		template<typename T>
		typename FEnumIterator<T>::Iterator end(FEnumIterator<T>)
		{
			return typename FEnumIterator<T>::Iterator(((int)T::Last) + 1);
		}
	}
}

#endif // _3FENGINE_SRC_UTILS_F_ENUM_ITERATOR_HPP_