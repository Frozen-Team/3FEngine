#pragma once

namespace FEngine {
	namespace Utils {
		template<typename T>
		class EnumIterator
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
		typename EnumIterator<T>::Iterator begin(EnumIterator<T>)
		{
			return typename EnumIterator<T>::Iterator((int)T::First);
		}

		template<typename T>
		typename EnumIterator<T>::Iterator end(EnumIterator<T>)
		{
			return typename EnumIterator<T>::Iterator(((int)T::Last) + 1);
		}
	}
}