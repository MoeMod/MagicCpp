#include <iostream>
#include <type_traits>

// C++17 std::conjunction does this... however I use just C++11
template<class...Args> auto SfinaeConjunction(decltype(Args(), std::true_type())...) -> std::true_type;
template<class...Args> auto SfinaeConjunction(...) -> std::false_type;
template<class...Args> struct Conjunction : decltype(SfinaeConjunction<Args...>(Args()...)) {};

// If all types are unique, Tag<T, ?> can be deduced. Sfinae based on that.
template<class T, std::size_t Index> struct Tag {};
template<class T, std::size_t Index> static auto SfinaeHelper(const Tag<T, Index> &) -> std::true_type;
template<class T/* no need Index */> static auto SfinaeHelper(...) -> std::false_type;

template<class List, class Seq> struct CheckTypeListUniqueImpl;
template<template<class...> class L, class...Args, std::size_t...I> struct CheckTypeListUniqueImpl<L<Args...>, std::index_sequence<I...>>
{
	struct Foo : Tag<Args, I >... {};
	using type = Conjunction<decltype(SfinaeHelper<Args>( Foo{} ))...>;
};

// just make_index_sequence and forward
template<class List> struct CheckTypeListUnique;
template<template<class...> class L, class...Args> struct CheckTypeListUnique<L<Args...>>
	: CheckTypeListUniqueImpl<L<Args...>, std::index_sequence_for<Args...>>::type {};

// simple test case
template<class...> struct TypeList;
int main()
{
	using A = TypeList<int, char, float, double>;
	using B = TypeList<int, float, char, int>;
	std::cout << CheckTypeListUnique<A>::value << CheckTypeListUnique<B>::value << std::endl;
}
