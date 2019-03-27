#include <iostream>
#include <tuple>
#include <type_traits>

template<template<class >class F> struct NotFn1
{
	template<class T> struct type
	{
		static constexpr bool value = !F<T>::value;
	};
};

template<class List, class Elem, template<class> class UnaryFunc> struct AppendIf;
template<template<class...>class L, class...T, class Elem, template<class> class UnaryFunc> struct AppendIf<L<T...>, Elem, UnaryFunc>
{
	using type = typename std::conditional<UnaryFunc<Elem>::value, L<T..., Elem>, L<T...>>::type;
};

template<class List, template<class> class UnaryFunc> struct RemoveIf;
template<template<class...>class L, class...AllElems, template<class> class UnaryFunc> struct RemoveIf<L<AllElems...>, UnaryFunc>
{
	template<class NewList, class...Rest> struct filter;
	template<class...Elems> struct filter<L<Elems...>>
	{
		using type = L<Elems...>;
	};
	template<class...Elems, class First, class...Rest> struct filter<L<Elems...>, First, Rest...>
	{
		using type = typename filter<typename AppendIf<L<Elems...>, First, UnaryFunc>::type, Rest...>::type;
	};
	using type = typename filter<L<>, AllElems...>::type;
};

template<class List, template<class> class DivideFunc> struct Partition
{
	using left = typename RemoveIf<List, DivideFunc>::type;
	using right = typename RemoveIf<List, NotFn1<DivideFunc>::template type>::type;
	using type = std::pair<left, right>;
};

template<class...Lists> struct ListCat;
template<class First> struct ListCat<First>
{
	using type = First;
};
template<template<class...>class L, class...A, class...B, class...Rest> struct ListCat<L<A...>, L<B...>, Rest...>
{
	using type = typename ListCat<L<A..., B...>, Rest...>::type;
};

template<class List, template<class, class> class CompareFunc> struct QSort;
template<template<class...>class L, class First, class...Rest, template<class, class> class CompareFunc> struct QSort<L<First, Rest...>, CompareFunc>
{
	template<class T>
	struct BindDivided : CompareFunc<First, T> {};
	using divided = Partition<L<Rest...>, NotFn1<BindDivided>::template type>;
	using type = typename ListCat<
			typename QSort<typename divided::left, CompareFunc>::type,
	        L<First>,
			typename QSort<typename divided::right, CompareFunc>::type
	>::type;
};
template<template<class...>class L, template<class, class> class CompareFunc> struct QSort<L<>, CompareFunc>
{
	using type = L<>;
};

template<class A, class B> struct SizeofCompare : std::integral_constant<bool, (sizeof(A) < sizeof(B))> {};

int main()
{
	using A = std::tuple<int, double, char, bool, void *>;
	using B = typename QSort<A, SizeofCompare>::type;
    std::cout << typeid(B).name() << std::endl;
}