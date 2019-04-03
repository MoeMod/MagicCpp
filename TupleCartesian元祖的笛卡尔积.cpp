#include <iostream>
#include <tuple>

template<class T, class Tuple2, std::size_t...I>
constexpr auto cart_ext_impl(std::tuple<T> a, Tuple2 rhs, std::index_sequence<I...>)
{
	return std::tuple<std::pair<T, typename std::tuple_element<I, Tuple2>::type>...>{
		{std::get<0>(a), std::get<I>(rhs)}...
	};
}

template<class T, class Tuple2>
constexpr auto cart_ext(std::tuple<T> a, Tuple2 rhs)
{
	return cart_ext_impl(a, rhs, std::make_index_sequence<std::tuple_size<Tuple2>::value>());
}

template<class Tuple1, class Tuple2, std::size_t...I>
constexpr auto cart_impl(Tuple1 lhs, Tuple2 rhs, std::index_sequence<I...>)
{
	return std::tuple_cat(cart_ext(std::tuple<typename std::tuple_element<I, Tuple1>::type>(std::get<I>(lhs)), rhs)...);
}

template<class Tuple1, class Tuple2>
constexpr auto cart(Tuple1 lhs, Tuple2 rhs)
{
	return cart_impl(lhs, rhs, std::make_index_sequence<std::tuple_size<Tuple1>::value>());
}

int main()
{
	int x = 1, y = 2, z = 3;
	auto tuple1 = std::tie(x, y, z);
	auto tuple2 = std::make_tuple("a", "b");
	auto tuple3 = cart(tuple2, tuple1);
	std::cout << typeid(tuple3).name() << std::endl;
	return 0;
}