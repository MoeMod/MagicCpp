#include <iostream>
#include <type_traits>

namespace Dalao {
    
    template<class T> struct type_identity { using type = T; };
    template<class Seq> struct MakeIndexFinder;
    template<size_t...I> struct MakeIndexFinder<std::index_sequence<I...>>
    {
        template<class T> type_identity<T> operator()(decltype(I, void()) *..., T *, ...);
    };
    template<size_t N, class List> struct ListFind;
    template<size_t N, template<class...>class L, class...Ts> struct ListFind<N, L<Ts...>>
    : decltype( MakeIndexFinder<std::make_index_sequence<N>>()(typename type_identity<Ts *>::type()...) ) {};
    
}

namespace Modern {
    
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
    
}

namespace Naive {
    
    template<size_t N, class List> struct ListFind;
    template<size_t N, template<class...>class L, class First, class...Rest> struct ListFind<N, L<First, Rest...>>
    : ListFind<N - 1, L<Rest...>> {};
    template<template<class...>class L, class First, class...Rest> struct ListFind<0, L<First, Rest...>>
    {
        using type = First;
    };
    
}

// Make some test case
template<class Seq> struct MakeTypelist;
template<size_t...I> struct MakeTypelist<std::index_sequence<I...>>
{
    using type = std::tuple<std::integral_constant<size_t, I>...>;
};
int main()
{
    using A = MakeTypelist<std::make_index_sequence<65535>>::type;
    
#define X 1
    
#if X == 1
    using B = Dalao::ListFind<255, A>::type;
#elif X == 2
    using B = Modern::ListFind<255, A>::type;
#else
    using B = Naive::ListFind<255, A>::type;
#endif
    std::cout << typeid(B).name() << std::endl;
    return 0;
}
