#include <iostream>
#include <type_traits>

// Modern one
template<size_t I, class T> struct Indexed { using type = T; };
template<class...Ts> struct MakeIndexFinder
{
	template<class Seq> struct impl;
	template<size_t...I> struct impl<std::index_sequence<I...>> : Indexed<I, Ts>... {};
	using type = impl<std::index_sequence_for<Ts...>>;
};
template<size_t N, class T> auto ListFindHelper(const Indexed<N, T> &) -> Indexed<N, T>;
template<size_t N, class List> struct ListFind;
template<size_t N, template<class...>class L, class...Ts> struct ListFind<N, L<Ts...>>
		: decltype(ListFindHelper<N>(typename MakeIndexFinder<Ts...>::type())) {};

// Naive one
template<size_t N, class List> struct ListFind2;
template<size_t N, template<class...>class L, class First, class...Rest> struct ListFind2<N, L<First, Rest...>>
		: ListFind2<N - 1, L<Rest...>> {};
template<template<class...>class L, class First, class...Rest> struct ListFind2<0, L<First, Rest...>>
{
	using type = First;
};

// Make some test case
template<class Seq, class T> struct MakeTypelist;
template<size_t...I, class T> struct MakeTypelist<std::index_sequence<I...>, T>
{
	using type = std::tuple<std::integral_constant<size_t, I*I>...>;
};
int main()
{
	using A = MakeTypelist<std::make_index_sequence<65536>, char>::type;
#if 1
	using B = ListFind<255, A>::type;
#else
	using B = ListFind2<255, A>::type;
#endif
	std::cout << typeid(B).name() << std::endl;
	return 0;
}