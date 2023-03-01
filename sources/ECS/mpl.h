#pragma once

// Samir Genaim

#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>

namespace mpl {

	// Lista de tipos en tiempo de compilación.
	template<typename ... Ts>
	struct TypeList {
		// Tamaño de la lista.
		static constexpr std::size_t size{ sizeof...(Ts) };
	};

	// IndexOf<T,TypeList<T1,T2,...>>() es la posición de T en T1, T2,...
	// podría usarse también <T,TypeList<T1,T2,...>>::value
	//
	template<typename, typename >
	struct IndexOf;

	// IndexOf caso base: encontrado el tipo que se busca.
	template<typename T, typename ... Ts>
	struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {
	};

	// IndexOf caso recursivo: 1 + IndexOf el resto de los tipos.
	template<typename T, typename TOther, typename ... Ts>
	struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant < std::size_t,
		1 + IndexOf<T, TypeList<Ts...>> { } > {
	};

	// Ith<i,TypeList<T1,T2,...>>::type es el tipo Ti
	//
	template<std::size_t i, typename >
	struct Ith;

	// Ith caso base: el tipo es primero en la lista.
	template<typename T, typename ... Ts>
	struct Ith<0, TypeList<T, Ts...>> {
		using type = T;
	};

	// Ith caso recursivo: el tipo es el (i-1)avo en el resto de la lista.
	template<std::size_t i, typename T, typename ... Ts>
	struct Ith<i, TypeList<T, Ts...>> {
		using type = typename Ith<i - 1, TypeList<Ts...>>::type;
	};

	// RemovePrefix<i,TypeList<T1,T2,...>>::type es TypeList<T_{i+1},T_{i+2},...>
	//
	// Ith<i,TypeList<T1,T2,...>>::type es el tipo Ti
	//
	template<std::size_t i, typename >
	struct RemovePrefix;

	// Ith caso base: nada para eliminar.
	template<typename T, typename ... Ts>
	struct RemovePrefix<0, TypeList<T, Ts...>> {
		using type = TypeList<T, Ts...>;
	};

	// Ith caso recursivo: elimina el (i-1)avo prefijo del resto de la lista.
	template<std::size_t i, typename T, typename ... Ts>
	struct RemovePrefix<i, TypeList<T, Ts...>> {
		using type = typename RemovePrefix<i - 1, TypeList<Ts...>>::type;
	};

	// si T1 es un tipo completo, es decir, no una declaración hacia delante, entonces
	// el 'tipo' terreno será T1, si no T2
	//
	template<class T1, class T2, class = void>
	struct is_complete_type {
		using type = T2;
	};

	template<class T1, class T2>
	struct is_complete_type<T1, T2,
		std::enable_if_t<
		std::is_object<T1>::value && !std::is_pointer<T1>::value
		&& (sizeof(T1) > 0)> > {
		using type = T1;
	};

	// numeric_type<max>::type es un tipo entero sin signo lo suficientemente grande para
	// poder contener el número máximo.
	//
	template<std::size_t max, class = void>
	struct numeric_type;

	template<std::size_t max>
	struct numeric_type<max,
		std::enable_if_t<(std::numeric_limits < uint8_t > ::max() >= max)> > {
		using type = uint8_t;
	};

	template<std::size_t max>
	struct numeric_type<max,
		std::enable_if_t<
		(std::numeric_limits < uint16_t > ::max() >= max)
		&& (std::numeric_limits < uint8_t > ::max() < max)> > {
		using type = uint16_t;
	};

	template<std::size_t max>
	struct numeric_type<max,
		std::enable_if_t<
		(std::numeric_limits < uint32_t > ::max() >= max)
		&& (std::numeric_limits < uint16_t > ::max() < max)> > {
		using type = uint32_t;
	};

}
