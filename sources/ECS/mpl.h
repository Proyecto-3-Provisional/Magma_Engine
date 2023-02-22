
#pragma once
#include <cstddef>
#include <type_traits>

namespace mpl {

	// Compile-time list of types.
	template<typename ... Ts>
	struct TypeList {
		// Size of the list.
		static constexpr std::size_t size{ sizeof...(Ts) };
	};

	template<typename, typename >
	struct IndexOf;

	// IndexOf base case: found the type we're looking for.
	template<typename T, typename ... Ts>
	struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {
	};

	// IndexOf recursive case: 1 + IndexOf the rest of the types.
	template<typename T, typename TOther, typename ... Ts>
	struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant < std::size_t,
		1 + IndexOf<T, TypeList<Ts...>>() > { //{} - ()
	};

	//template<typename>
	//struct Count : std::integral_constant<int, 0> {};
	//
	//template<typename ... Ts>
	//struct Count< TypeList<Ts...>> : std::integral_constant < int, 1 + Count< TypeList<Ts...>>()> {};
	//class A;
	//class B;
	//class C;
	//
	//template<typename T>
	//constexpr int n = Count<TypeList<A, B, C>>();
	//
	//
	//template<typename, typename >
	//struct Occurrences;
	//
	//template<typename T, typename ... Ts>
	//struct Occurrences<T, TypeList<Ts...>> : std::integral_constant<std::int, 0> {};
	//
	//template<typename T, typename TOther, typename ... Ts>
	//struct Occurrences<T, TypeList<TOther, Ts...>> : std::integral_constant < std::int,
	//	1 + Occurrences<T, TypeList<Ts...>>() > { //{} - ()
	//};
}