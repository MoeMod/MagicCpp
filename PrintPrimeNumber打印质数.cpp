#include <iostream>
#include <array>
#include <type_traits>

constexpr size_t log2(size_t N)
{
	return N == 1 ? 0 : log2(N >> 1) + 1;
}

template<class...Seq> struct SequenceCat;
template<class A> struct SequenceCat<A> { using type = A; };
template<size_t...I1, size_t...I2> struct SequenceCat<std::index_sequence<I1...>, std::index_sequence<I2...>>
{
	using type = std::index_sequence<I1..., I2...>;
};
template<class A, class B, class...Rest> struct SequenceCat<A, B, Rest...>
		: SequenceCat<
			typename SequenceCat<A, B>::type,
			typename SequenceCat<Rest...>::type
		>{};

template<class Seq, template<size_t> class F> struct SequenceRemoveIf;
template<size_t...I, template<size_t> class F> struct SequenceRemoveIf <std::index_sequence<I...>, F>
		: SequenceCat<
			typename std::conditional<
				F<I>::value,
				std::index_sequence<>,
				std::index_sequence<I>
			>::type...
		>{};
template<template<size_t> class F> struct SequenceRemoveIf <std::index_sequence<>, F>
{
	using type = std::index_sequence<>;
};

template<class Seq, size_t N> struct SequenceAdd;
template<size_t...I, size_t N> struct SequenceAdd<std::index_sequence<I...>, N>
{
	using type = std::index_sequence<(I + N)...>;
};

template<size_t N> struct MakePrimeSequence
{
	template<class, class> struct Process;
	template<class Seq, size_t First, size_t...Rest> struct Process<Seq, std::index_sequence<First, Rest...>>
	{
		template<size_t X> struct lambda : std::integral_constant <bool, (X < 2) || (X > First && X % First == 0)> {};

		using type = typename Process<
				typename SequenceRemoveIf<Seq, lambda>::type,
				typename SequenceRemoveIf<std::index_sequence<Rest...>, lambda>::type
			>::type;
	};
	template<class Seq> struct Process<Seq, std::index_sequence<>>
	{
		using type = Seq;
	};

	using type = typename Process<
			std::make_index_sequence<N>,
			typename SequenceAdd<std::make_index_sequence<(1 << (log2(N) / 2 + 1)) - 2>, 2>::type
			>::type;
};

template<size_t...I>
constexpr auto SequenceToArray(std::index_sequence<I...>) -> std::array<size_t, sizeof...(I)>
{
	return {I...};
}

constexpr size_t N = 2000;
constexpr auto PrimeTable = SequenceToArray(typename MakePrimeSequence<N>::type());

int main()
{
	for(auto i : PrimeTable)
		std::cout << i << std::endl;
	return 0;
}
